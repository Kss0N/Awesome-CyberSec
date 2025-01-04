#include "pch.h"
#include "public/Base-Conversion.h"

#include <intrin.h>

static const char* zBase64Table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const char* zBase64urlTable = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";

static char encode64(uint8_t value, bool bUrl) 
{    
    return bUrl ? zBase64urlTable[value] : zBase64Table[value];
}

static uint8_t decode64(char value, bool bUrl)
{
    if ('A' <= value && value <= 'Z')
        return value - 'A' + zBase64Table['A'];
    if ('a' <= value && value <= 'z')
        return value - 'z' + zBase64Table['a'];
    if ('0' <= value && value <= '9')
        return value - '0' + zBase64Table['0'];

    if ((value == '+' && !bUrl) ||
        (value == '-' && bUrl))
        return 62;

    if ((value == '/' && !bUrl) || 
        (value == '_' && bUrl))
        return 63;

    return 0xC0; // invalid bit sequence, it is above 63.
}

static void encodeBucket(char output[4], uint8_t input[3], bool bUrl)
{
    //
    // AAAAAABB BBBBCCCC CCDDDDDD
    //

    const uint8_t
        a = (input[0] & 0xFC) >> 2,                           // 00AAAAAA
        b = (input[0] & 0x03) << 4 | (input[1] & 0xF0) >> 4, // 00BBBBBB
        c = (input[1] & 0x0F) << 2 | (input[2] & 0xC0) >> 6, // 00CCCCCC
        d = (input[2] & 0x3F);                                // 00DDDDDD

    output[0] = encode64(a, bUrl);
    output[1] = encode64(b, bUrl);
    output[2] = encode64(c, bUrl);
    output[3] = encode64(d, bUrl);
}

static int decodeBucket(uint8_t output[3], char input[4], bool bUrl)
{
    const uint8_t
        a = decode64(input[0], bUrl), // 00AAAAAA
        b = decode64(input[1], bUrl), // 00BBBBBB
        c = decode64(input[2], bUrl), // 00CCCCCC
        d = decode64(input[3], bUrl); // 00DDDDDD

    // Make sure they're from valid base64
    // At least one of these being invalid will render entire entire sequence invalid.
    if ((a|b|c|d) & 0xC0)
    {
        return -1;
    }

    output[0] = (a << 2) + (b >> 4);
    output[1] = (b << 4) + (c >> 2);
    output[2] = (c << 6) + (d >> 0);

    return 0;
}




static std::string convertToBase64(std::span<uint8_t> data, bool bUrl)
{
    if (data.size() == 0)
        return "";

    std::string ret;
    ret.reserve((4 * data.size()) / 3); // On average base64 encodings will be 1.333... times larger. (3 bytes -> 4 characters)

    char output[4];
    uint8_t bucket[3];

    memcpy(bucket, data.data(), 3);

    ret.resize(4);
    encodeBucket(ret.data(), bucket, bUrl);

    return ret;


    //uint8_t bucket[3];
    const uint32_t paddedSize = data.size() % 3 != 0 ?
        data.size() + (3 - data.size() % 3) :
        data.size();
    int ix = 0;



    


    return ret;
}





std::string sec::toBase64(const std::span<uint8_t> data) noexcept
{
    return convertToBase64(data, false);
}

std::string sec::toBase64(const std::string_view data) noexcept
{
    return sec::toBase64(std::span<uint8_t>((uint8_t*)&*data.begin(), data.size()));
}


std::string sec::toBase64url(const std::span<uint8_t> data) noexcept
{
    return convertToBase64(data, true);
}

std::string sec::toBase64url(const std::string_view data) noexcept
{
    return sec::toBase64url(std::span<uint8_t>((uint8_t*)&*data.begin(), data.size()));
}
