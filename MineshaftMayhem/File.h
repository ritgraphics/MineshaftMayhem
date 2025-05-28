
#pragma once

/// @brief File class for reading and writing files using Win32 API.
class File
{
public:
    enum class FileAccess : uint32_t
    {
        READ = GENERIC_READ,      ///< Open file for reading.
        WRITE = GENERIC_WRITE,    ///< Open file for writing.
        READ_WRITE = READ | WRITE ///< Open file for reading and writing.
    };

    /// @brief Constructs a File object for the specified file name and access mode.
    /// @param [in] lpFileName A pointer to a wide-character string that specifies the name of the file to open.
    /// @param [in] access The desired access mode for the file. Defaults to FileAccess::Read if not specified.
    /// @throws std::runtime_error if the file cannot be opened.
    explicit File(_In_ LPCWSTR lpFileName, _In_opt_ FileAccess access = FileAccess::READ);
    /// @brief Constructs a File object for the specified file name with the given access mode.
    /// @param lpFileName A pointer to a null-terminated string that specifies the name of the file to open.
    /// @param access The desired access mode for the file (e.g., read, write). Defaults to FileAccess::Read if not
    /// specified.
    /// @throws std::runtime_error if the file cannot be opened.
    explicit File(_In_ LPCSTR lpFileName, _In_opt_ FileAccess access = FileAccess::READ);

    /// @brief Reads a sequence of wide characters from the specified offset and size.
    /// @param [in] offset The starting position from which to begin reading.
    /// @param [in] size The number of wide characters to read.
    /// @return A vector containing the wide characters read from the specified range.
    /// @throws std::runtime_error if the read operation fails.
    std::vector<WCHAR>   Read(_In_ size_t offset, _In_ size_t size) const;
    /// @brief Reads a sequence of wide characters from the file starting at the specified offset.
    /// @param [in] offset The starting position in the file from which to begin reading.
    /// @param [in] size The number of wide characters to read.
    /// @return A std::wstring containing the characters read from the specified offset and size.
    /// @throws std::runtime_error if the read operation fails.
    std::wstring         ReadText(_In_ size_t offset, _In_ size_t size) const;
    /// @brief Reads and returns all bytes from the file.
    /// @return A vector containing all bytes read from the source.
    /// @throws std::runtime_error if the read operation fails.
    std::vector<uint8_t> ReadAll() const;

    /// @brief Writes a sequence of wide characters to the file.
    /// @param [in] data Pointer to the wide character data to write.
    /// @param [in] size The number of wide characters to write.
    /// @throws std::runtime_error if the write operation fails.
    void                 Write(_In_ LPCWSTR data, _In_ size_t size) const;
    /// @brief Writes the specified wide string data to the file.
    /// @param [in] data The wide string view containing the data to write.
    void                 Write(_In_ std::wstring_view data) const;
    /// @brief Writes a wide string to the file at the specified offset.
    /// @param [in] offset The position in file at which to begin writing the data.
    /// @param [in] data The wide string view containing the data to write.
    /// @throws std::runtime_error if the write operation fails.
    void                 Write(_In_ size_t offset, _In_ std::wstring_view data) const;
    /// @brief Writes a block of wide-character data at the specified offset.
    /// @param [in] offset The position in file at which to begin writing the data.
    /// @param [in] data A pointer to the wide-character data to write.
    /// @param size The number of wide characters to write.
    /// @throws std::runtime_error if the write operation fails.
    void                 Write(_In_ size_t offset, _In_ LPCWSTR data, _In_ size_t size) const;

private:
    winrt::handle m_hFile; ///< Handle to file.
};
