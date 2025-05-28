#include "pch.h"
#include "File.h"

#include <filesystem>

namespace
{
    DWORD GetCreationDisposition(File::FileAccess access)
    {
        switch (access)
        {
        case File::FileAccess::READ:
            return OPEN_EXISTING;
        case File::FileAccess::WRITE:
            return TRUNCATE_EXISTING;
        case File::FileAccess::READ_WRITE:
            return OPEN_ALWAYS;
        default:
            throw std::invalid_argument("Invalid file access type.");
        }
    }

    std::filesystem::path GetBasePath()
    {
        wchar_t path[MAX_PATH];
        DWORD   dwLength = GetModuleFileNameW(nullptr, path, MAX_PATH);
        if (dwLength == 0 || dwLength == MAX_PATH)
            throw std::runtime_error("Failed to access executable path");

        return std::filesystem::path(path).parent_path();
    }

} // namespace

File::File(_In_ LPCWSTR lpFileName, _In_opt_ FileAccess access) : m_hFile(INVALID_HANDLE_VALUE)
{
    const DWORD dwCreationDisposition = GetCreationDisposition(access);
    auto        filePath = GetBasePath();
    filePath.append(lpFileName);

    HANDLE hFile = CreateFileW(filePath.wstring().c_str(), std::underlying_type_t<FileAccess>(access), FILE_SHARE_READ,
                               nullptr, dwCreationDisposition, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        const auto error = GetLastError();
        LPSTR      message = nullptr;
        size_t szMessageLength = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, nullptr,
                                                error, 0, (LPSTR)&message, 0, nullptr);
        const auto exception = std::format("Failed to open file: {}", message);
        LocalFree(message);
        throw std::runtime_error(exception);
    }

    m_hFile.attach(hFile);
}

File::File(_In_ LPCSTR lpFileName, _In_opt_ FileAccess access) : m_hFile(INVALID_HANDLE_VALUE)
{
    const DWORD dwCreationDisposition = GetCreationDisposition(access);

    auto filePath = GetBasePath();
    filePath.append(lpFileName);

    HANDLE hFile = CreateFileA(filePath.string().c_str(), std::underlying_type_t<FileAccess>(access), FILE_SHARE_READ,
                               nullptr, dwCreationDisposition, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        const auto error = GetLastError();
        LPSTR      message = nullptr;
        size_t szMessageLength = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, nullptr,
                                                error, 0, (LPSTR)&message, 0, nullptr);
        const auto exception = std::format("Failed to open file: {}", message);
        LocalFree(message);
        throw std::runtime_error(exception);
    }

    m_hFile.attach(hFile);
}

std::wstring File::ReadText(_In_ size_t offset, _In_ size_t count) const
{
    return std::wstring(Read(offset, count).data(), count);
}

std::vector<WCHAR> File::Read(_In_ size_t offset, _In_ size_t count) const
{
    if (offset > std::numeric_limits<DWORD>::max() || count > std::numeric_limits<DWORD>::max())
        throw std::runtime_error("Offset or count exceeds maximum DWORD value.");

    if (count == 0)
        return {};

    std::vector<WCHAR> buffer(count);
    DWORD              dwBytesRead{};
    if (!SetFilePointerEx(m_hFile.get(), {static_cast<ULONG>(offset)}, nullptr, FILE_BEGIN))
    {
        const auto error = GetLastError();
        LPSTR      message = nullptr;
        size_t szMessageLength = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, nullptr,
                                                error, 0, (LPSTR)&message, 0, nullptr);
        const auto exception = std::format("Failed to set file pointer: {}", message);
        LocalFree(message);
        throw std::runtime_error(exception);
    }

    if (!ReadFile(m_hFile.get(), buffer.data(), static_cast<DWORD>(count), &dwBytesRead, nullptr))
    {
        const auto error = GetLastError();
        LPSTR      message = nullptr;
        size_t szMessageLength = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, nullptr,
                                                error, 0, (LPSTR)&message, 0, nullptr);
        const auto exception = std::format("Failed to read bytes from file: {}", message);
        LocalFree(message);
        throw std::runtime_error(exception);
    }

    if (dwBytesRead < count)
        throw std::runtime_error("ReadFile limit reached. Re-write to support files larger than 4GB");

    return buffer;
}

std::vector<uint8_t> File::ReadAll() const
{
    LARGE_INTEGER fileSize{};
    if (!GetFileSizeEx(m_hFile.get(), &fileSize))
    {
        const auto error = GetLastError();
        LPSTR      message = nullptr;
        size_t szMessageLength = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, nullptr,
                                                error, 0, (LPSTR)&message, 0, nullptr);
        const auto exception = std::format("Failed to get file size: ", message);
        LocalFree(message);
        throw std::runtime_error(exception);
    }

    if (fileSize.QuadPart == 0)
        return {};

    std::vector<uint8_t> buffer(fileSize.QuadPart);
    DWORD                dwBytesRead{};
    if (!ReadFile(m_hFile.get(), buffer.data(), buffer.size(), &dwBytesRead, nullptr))
    {
        const auto error = GetLastError();
        LPSTR      message = nullptr;
        size_t szMessageLength = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, nullptr,
                                                error, 0, (LPSTR)&message, 0, nullptr);
        const auto exception = std::format("Failed to read bytes from file: ", message);
        LocalFree(message);
        throw std::runtime_error(exception);
    }

    if (dwBytesRead < buffer.size())
        throw std::runtime_error("ReadFile limit reached. Re-write to support files larger than 4GB");

    // Reset file handle to beginning for subsequent reads.
    SetFilePointerEx(m_hFile.get(), {0}, nullptr, FILE_BEGIN);

    return buffer;
}

void File::Write(_In_ std::wstring_view data) const
{
    Write(data.data(), data.size());
}

void File::Write(_In_ LPCWSTR data, _In_ size_t size) const
{
    if (size > std::numeric_limits<DWORD>::max())
        throw std::runtime_error("Size exceeds maximum DWORD value.");

    if (size == 0 || data == nullptr)
        return;

    // Move file pointer to the specified offset
    LARGE_INTEGER liOffset;
    liOffset.QuadPart = static_cast<LONGLONG>(0);
    if (!SetFilePointerEx(m_hFile.get(), liOffset, nullptr, FILE_END))
    {
        const auto error = GetLastError();
        LPSTR      message = nullptr;
        FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, nullptr, error, 0, (LPSTR)&message,
                       0, nullptr);
        const auto exception = std::format("Failed to set file pointer: {}", message);
        LocalFree(message);
        throw std::runtime_error(exception);
    }

    // Write the data (size is in WCHARs, so multiply by sizeof(WCHAR))
    DWORD bytesToWrite = static_cast<DWORD>(size * sizeof(WCHAR));
    DWORD bytesWritten = 0;
    if (!WriteFile(m_hFile.get(), data, bytesToWrite, &bytesWritten, nullptr))
    {
        const auto error = GetLastError();
        LPSTR      message = nullptr;
        FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, nullptr, error, 0, (LPSTR)&message,
                       0, nullptr);
        const auto exception = std::format("Failed to write to file: {}", message);
        LocalFree(message);
        throw std::runtime_error(exception);
    }

    if (bytesWritten < bytesToWrite)
        throw std::runtime_error("WriteFile did not write all bytes.");
}

void File::Write(_In_ size_t offset, _In_ std::wstring_view data) const
{
    Write(offset, data.data(), data.size());
}

void File::Write(_In_ size_t offset, _In_ LPCWSTR data, _In_ size_t size) const
{
    if (offset > std::numeric_limits<DWORD>::max() || size > std::numeric_limits<DWORD>::max())
        throw std::runtime_error("Offset or size exceeds maximum DWORD value.");

    if (size == 0 || data == nullptr)
        return;

    // Move file pointer to the specified offset
    LARGE_INTEGER liOffset;
    liOffset.QuadPart = static_cast<LONGLONG>(offset);
    if (!SetFilePointerEx(m_hFile.get(), liOffset, nullptr, FILE_END))
    {
        const auto error = GetLastError();
        LPSTR      message = nullptr;
        FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, nullptr, error, 0, (LPSTR)&message,
                       0, nullptr);
        const auto exception = std::format("Failed to set file pointer: {}", message);
        LocalFree(message);
        throw std::runtime_error(exception);
    }

    // Write the data (size is in WCHARs, so multiply by sizeof(WCHAR))
    DWORD bytesToWrite = static_cast<DWORD>(size * sizeof(WCHAR));
    DWORD bytesWritten = 0;
    if (!WriteFile(m_hFile.get(), data, bytesToWrite, &bytesWritten, nullptr))
    {
        const auto error = GetLastError();
        LPSTR      message = nullptr;
        FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, nullptr, error, 0, (LPSTR)&message,
                       0, nullptr);
        const auto exception = std::format("Failed to write to file: {}", message);
        LocalFree(message);
        throw std::runtime_error(exception);
    }

    if (bytesWritten < bytesToWrite)
        throw std::runtime_error("WriteFile did not write all bytes.");
}