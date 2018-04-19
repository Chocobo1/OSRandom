/*
 *  Chocobo1/OSRandom
 *
 *   Copyright 2018 by Mike Tzou (Chocobo1)
 *     https://github.com/Chocobo1/OSRandom
 *
 *   Licensed under GNU General Public License 3 or later.
 *
 *  @license GPL3 <https://www.gnu.org/licenses/gpl-3.0-standalone.html>
 */

#ifndef CHOCOBO1_OSRANDOM_HPP
#define CHOCOBO1_OSRANDOM_HPP

#include <cstdio>
#include <cstdlib>

namespace Chocobo1
{
    void fatal(const char *msg)
    {
        fprintf(stderr, "%s\n", msg);
        abort();
    }
}

#ifdef _WIN32

#include <cstdint>
#include <cwchar>
#include <limits>

#ifndef NOMINMAX  // no one should use these abominations
#define NOMINMAX
#endif
#include <Windows.h>
#undef min
#undef max

#include <Ntsecapi.h>

namespace Chocobo1
{
class OSRandom
{
    // need to satisfy UniformRandomBitGenerator requirements

    public:
        using result_type = uint32_t;

        OSRandom()
        {
            wchar_t sysPath[MAX_PATH] = {0};

            const UINT len = ::GetSystemDirectoryW(sysPath, (MAX_PATH - 1));
            if (len == 0)
                fatal("GetSystemDirectoryW() failed");

            if (sysPath[len - 1] != L'\\')
                wcscat_s(sysPath, MAX_PATH, L"\\");
            wcscat_s(sysPath, MAX_PATH, L"Advapi32.dll");

            m_rtlGenRandomAPI = reinterpret_cast<decltype(m_rtlGenRandomAPI)>(
                ::GetProcAddress(::LoadLibraryW(sysPath), "SystemFunction036"));
            if (!m_rtlGenRandomAPI)
                fatal("Load RtlGenRandom() failed");
        }

        static constexpr result_type min()
        {
            return std::numeric_limits<result_type>::min();
        }

        static constexpr result_type max()
        {
            return std::numeric_limits<result_type>::max();
        }

        result_type operator() ()
        {
            result_type buf = 0;
            const bool result = m_rtlGenRandomAPI(&buf, sizeof(buf));
            if (!result)
                fatal("RtlGenRandom() failed");

            return buf;
        }


    private:
        using Sig = BOOLEAN (WINAPI *) (PVOID, ULONG);
        Sig m_rtlGenRandomAPI;
};
}

#else  // _WIN32

#include <cstdint>
#include <limits>

namespace Chocobo1
{
class OSRandom
{
    // need to satisfy UniformRandomBitGenerator requirements

    public:
        using result_type = uint32_t;

        OSRandom()
            : m_randDev {fopen("/dev/urandom", "rb")}
        {
            if (!m_randDev)
                fatal("Open /dev/urandom failed");
        }

        ~OSRandom()
        {
            if (m_randDev)
                fclose(m_randDev);
        }

        static constexpr result_type min()
        {
            return std::numeric_limits<result_type>::min();
        }

        static constexpr result_type max()
        {
            return std::numeric_limits<result_type>::max();
        }

        result_type operator() () const
        {
            result_type buf = 0;
            if (fread(&buf, sizeof(buf), 1, m_randDev) != 1)
                fatal("Read /dev/urandom failed");

            return buf;
        }

    // error diagnosis
        int ferror() const
        {
            return ::ferror(m_randDev);
        }

        bool eof() const
        {
            return (::feof(m_randDev) != 0);
        }

        bool good() const
        {
            return ((ferror() == 0) && !eof());
        }


    private:
        FILE *m_randDev;
};
}

#endif  // _WIN32

#endif  // CHOCOBO1_OSRANDOM_HPP
