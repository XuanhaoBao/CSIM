/*
 *  FastCSIM Copyright (C) 2021 cassuto                                    
 *  This project is free edition; you can redistribute it and/or           
 *  modify it under the terms of the GNU Lesser General Public             
 *  License(LGPL) as published by the Free Software Foundation; either      
 *  version 2.1 of the License, or (at your option) any later version.     
 *                                                                         
 *  This project is distributed in the hope that it will be useful,        
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU      
 *  Lesser General Public License for more details.                        
 */

#ifndef CSIM_VARIANT_H_
#define CSIM_VARIANT_H_

#include "csim/model/Types.h"
#include <string>
#include <vector>

namespace csimModel
{

    class PropertyMdl;

    class Variant
    {
    public:
        enum VariantType
        {
            VariantUnknown = 0,
            VariantUint8,
            VariantUint16,
            VariantUint32,
            VariantUint64,
            VariantInt8,
            VariantInt16,
            VariantInt32,
            VariantInt64,
            VariantDouble,
            VariantBoolean,
            VariantString,
            VariantPropertyModel
        };

        Variant();
        explicit Variant(VariantType type);
        Variant(const Variant &src);

        VariantType getType() const;

        Variant &setUint8(uint8_t u8);
        Variant &setUint16(uint16_t u16);
        Variant &setUint32(uint32_t u32);
        Variant &setUint64(uint64_t u64);
        Variant &setInt8(int8_t i8);
        Variant &setInt16(int16_t i16);
        Variant &setInt32(int32_t i32);
        Variant &setInt64(int64_t i64);
        Variant &setDouble(double d);
        Variant &setBoolean(bool b);
        Variant &setString(const char *str);
        Variant &setPropertyModel(PropertyMdl *mdl);

        uint8_t getUint8() const;
        uint16_t getUint16() const;
        uint32_t getUint32() const;
        uint64_t getUint64() const;
        int8_t getInt8() const;
        int16_t getInt16() const;
        int32_t getInt32() const;
        int64_t getInt64() const;
        double getDouble() const;
        bool getBoolean() const;
        const char *getString() const;
        PropertyMdl *getPropertyModel() const;

    private:
        VariantType m_type;
        union
        {
            uint8_t u8;
            uint16_t u16;
            uint32_t u32;
            uint64_t u64;
            int8_t i8;
            int16_t i16;
            int32_t i32;
            int64_t i64;
            float f;
            double d;
            bool b;
            PropertyMdl *mdl;
        } m_dat;
        std::string m_str;
    };

}

#endif // CSIM_VARIANT_H_