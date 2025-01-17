#pragma once
#include <map>
#include <vector>
#include <string>
#include <stdexcept>
#include <cstring> // Для std::memcpy
#include <nlohmann/json.hpp> 

#include "ITickable.h"
#include "Core/GlobalIDGenerator.h"

using json = nlohmann::json;

struct PropertyInfo {
    uint64_t ID;
    void* ValuePtr; 
    size_t Size;    

    PropertyInfo(const uint64_t InId, void* InValuePtr, size_t InSize)
        : ID(InId), ValuePtr(InValuePtr), Size(InSize) {}
};

class Object : public ITickable {
protected:
    Object();

    void Tick(const float DeltaSeconds) override;

public:
    virtual void BeginPlay();

    template <typename T>
    void RegisterProperty(T& PropertyReference) {
        uint64_t PropertyID = GlobalIDGenerator::GetInstance().GetNextID();
        Properties[PropertyID] = PropertyInfo(PropertyID, &PropertyReference, sizeof(T));
    }

    template <typename T>
    T GetProperty(const uint64_t PropertyID) const {
        if (Properties.find(PropertyID) != Properties.end()) {
            return *reinterpret_cast<T*>(Properties.at(PropertyID).ValuePtr);
        }
        throw std::runtime_error("Property not found or type mismatch");
    }

    json SerializeToJson() const {
        json JsonData;

        for (const auto& [ID, Info] : Properties) {
            uint8_t* BytePtr = reinterpret_cast<uint8_t*>(Info.ValuePtr);
            std::vector<uint8_t> Bytes(BytePtr, BytePtr + Info.Size);
            JsonData[std::to_string(ID)] = Bytes;
        }

        return JsonData;
    }

    void DeserializeFromJson(const json& JsonData) {
        for (const auto& [IDStr, ByteArray] : JsonData.items()) {
            uint64_t ID = std::stoull(IDStr);

            if (Properties.find(ID) != Properties.end()) {
                PropertyInfo& Info = Properties[ID];
                const auto& Bytes = ByteArray.get<std::vector<uint8_t>>();

                if (Bytes.size() != Info.Size) {
                    throw std::runtime_error("Size mismatch during deserialization");
                }

                std::memcpy(Info.ValuePtr, Bytes.data(), Info.Size);
            } else {
                throw std::runtime_error("Unknown property ID during deserialization");
            }
        }
    }

protected:
    Object* Owner = nullptr;

    bool IsGarbage = false;
    bool CanTick = true;

    std::map<uint64_t, PropertyInfo> Properties;

public:
    void SetOwner(Object* NewOwner) {
        Owner = NewOwner;
    }

    void SetCanTick(const bool bCanTick) {
        CanTick = bCanTick;
    }

    void MarkAsGarbage() { IsGarbage = true; }

    virtual void RegisterPropertiesBase();
};
