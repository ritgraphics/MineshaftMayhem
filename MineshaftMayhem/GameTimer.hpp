////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Matt Guerrette 2023-2025
// SPDX-License-Identifier: MIT
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <algorithm>
#include <atomic>

class GameTimer
{
    static constexpr uint64_t TicksPerSecond = 10000000;

public:
    GameTimer();

    ~GameTimer() = default;

    [[nodiscard]] uint64_t GetElapsedTicks() const noexcept;

    [[nodiscard]] double   GetElapsedSeconds() const noexcept;

    [[nodiscard]] uint64_t GetTotalTicks() const noexcept;

    [[nodiscard]] double   GetTotalSeconds() const noexcept;

    [[nodiscard]] uint32_t GetFrameCount() const noexcept;

    [[nodiscard]] uint32_t GetFramesPerSecond() const noexcept;

    void                   SetFixedTimeStep(bool isFixedTimeStep) noexcept;

    void                   SetTargetElapsedTicks(uint64_t targetElapsed) noexcept;

    void                   SetTargetElapsedSeconds(double targetElapsed) noexcept;

    void                   ResetElapsedTime();

    template <typename TUpdate>
    void Tick(const TUpdate& update)
    {
        LARGE_INTEGER currentTime;
        QueryPerformanceCounter(&currentTime);

        uint64_t delta = currentTime.QuadPart - QpcLastTime.QuadPart;
        QpcLastTime = currentTime;
        QpcSecondCounter += delta;

        delta = std::clamp(delta, static_cast<uint64_t>(0), QpcMaxDelta);
        delta *= TicksPerSecond;
        delta /= static_cast<uint64_t>(QpcFrequency.QuadPart);

        const uint32_t lastFrameCount = FrameCount;
        if (IsFixedTimeStep)
        {
            if (static_cast<uint64_t>(std::abs(static_cast<int64_t>(delta - TargetElapsedTicks))) <
                TicksPerSecond / 4000)
            {
                delta = TargetElapsedTicks;
            }

            LeftOverTicks += delta;
            while (LeftOverTicks >= TargetElapsedTicks)
            {
                ElapsedTicks = TargetElapsedTicks;
                TotalTicks += TargetElapsedTicks;
                LeftOverTicks -= TargetElapsedTicks;
                FrameCount++;

                update();
            }
        }
        else
        {
            ElapsedTicks = delta;
            TotalTicks += delta;
            LeftOverTicks = 0;
            FrameCount++;

            update();
        }

        if (FrameCount != lastFrameCount)
        {
            FramesThisSecond++;
        }

        if (QpcSecondCounter >= static_cast<uint64_t>(QpcFrequency.QuadPart))
        {
            FramesPerSecond = FramesThisSecond;
            FramesThisSecond = 0;
            QpcSecondCounter %= QpcFrequency.QuadPart;
        }
    }

    static constexpr double TicksToSeconds(const uint64_t ticks) noexcept
    {
        return static_cast<double>(ticks) / TicksPerSecond;
    }

    static constexpr uint64_t SecondsToTicks(const double seconds) noexcept
    {
        return static_cast<uint64_t>(seconds * TicksPerSecond);
    }

    // New method to calculate interpolation factor
    [[nodiscard]] double GetInterpolationFactor() const noexcept
    {
        if (IsFixedTimeStep)
        {
            return static_cast<double>(LeftOverTicks) / static_cast<double>(TargetElapsedTicks);
        }
        return 0.0; // No interpolation needed for variable timestep
    }

private:
    LARGE_INTEGER        QpcFrequency;
    LARGE_INTEGER        QpcLastTime;
    uint64_t             QpcMaxDelta;
    uint64_t             QpcSecondCounter;
    uint64_t             ElapsedTicks;
    uint64_t             TotalTicks;
    std::atomic_uint64_t LeftOverTicks;
    uint32_t             FrameCount;
    uint32_t             FramesPerSecond;
    uint32_t             FramesThisSecond;
    bool                 IsFixedTimeStep;
    std::atomic_uint64_t TargetElapsedTicks;
};
