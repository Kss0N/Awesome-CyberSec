/**

    @file      Base-Conversion.h
    @brief     Utilities for Base convertions.
    @details   ~
    @author    Jakob Kristersson <jakob@kristerson.se>
    @date      3.01.2025

**/
#pragma once
#include <stdint.h>
#include <string>
#include <string_view>

#include <vector>
#include <span>


namespace sec {

    /**
        @brief   Encodes span of binary data into a base64 ascii-string.
        @details Base64 takes on a bigger structure, on average log3(4) times more; 3 bytes of data needs for characters (= bytes) of Base64.
            See RFC4648 for more details.
        @param   data span of binary data.
        @returns      base64 encoded string.
    **/
    std::string toBase64(const std::span<uint8_t> data) noexcept;

    /**
        @brief   Encodes string into a base64 ascii-string.
        @param   data view of string.
        @returns      base64 encoded string.
    **/
    std::string toBase64(const std::string_view data) noexcept;

    /**
        @brief   Encodes span of binary data into a base64 ascii-string using the URL compliant variant.
        @details Base64 takes on a bigger structure, on average log3(4) times more; 3 bytes of data needs for characters (= bytes) of Base64.
            The URL variant replaces '+' (for 62 in base10) with '-' and '/' (63 in base10) with '_' so that the output format
            See RFC4648 for more details.
        @param   data 
        @returns      
    **/
    std::string toBase64url(const std::span<uint8_t>) noexcept;


    std::string toBase64url(const std::string_view) noexcept;

    
    std::vector<uint8_t> fromBase64(std::string_view);


    std::vector<uint8_t> fromtBase64url(std::string_view);
    
}