// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: plant.proto

#include "plant.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG
namespace wanderer {
namespace proto {
constexpr Plant::Plant(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : tiles_()
  , _tiles_cached_byte_size_(0)
  , tall_tiles_()
  , _tall_tiles_cached_byte_size_(0)
  , current_growth_(0)
  , rate_(0)
  , base_y_(0)
  , tile_height_(0)
  , index_(uint64_t{0u}){}
struct PlantDefaultTypeInternal {
  constexpr PlantDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~PlantDefaultTypeInternal() {}
  union {
    Plant _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PlantDefaultTypeInternal _Plant_default_instance_;
}  // namespace proto
}  // namespace wanderer
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_plant_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_plant_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_plant_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_plant_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::Plant, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::Plant, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::Plant, current_growth_),
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::Plant, rate_),
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::Plant, base_y_),
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::Plant, tile_height_),
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::Plant, index_),
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::Plant, tiles_),
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::Plant, tall_tiles_),
  0,
  1,
  2,
  3,
  4,
  ~0u,
  ~0u,
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 13, -1, sizeof(::wanderer::proto::Plant)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::wanderer::proto::_Plant_default_instance_),
};

const char descriptor_table_protodef_plant_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\013plant.proto\022\016wanderer.proto\"\346\001\n\005Plant\022"
  "\033\n\016current_growth\030\001 \001(\002H\000\210\001\001\022\021\n\004rate\030\002 \001"
  "(\002H\001\210\001\001\022\023\n\006base_y\030\003 \001(\002H\002\210\001\001\022\030\n\013tile_hei"
  "ght\030\004 \001(\005H\003\210\001\001\022\022\n\005index\030\005 \001(\004H\004\210\001\001\022\021\n\005ti"
  "les\030\006 \003(\005B\002\020\001\022\026\n\ntall_tiles\030\007 \003(\005B\002\020\001B\021\n"
  "\017_current_growthB\007\n\005_rateB\t\n\007_base_yB\016\n\014"
  "_tile_heightB\010\n\006_indexb\006proto3"
  ;
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_plant_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_plant_2eproto = {
  false, false, 270, descriptor_table_protodef_plant_2eproto, "plant.proto", 
  &descriptor_table_plant_2eproto_once, nullptr, 0, 1,
  schemas, file_default_instances, TableStruct_plant_2eproto::offsets,
  file_level_metadata_plant_2eproto, file_level_enum_descriptors_plant_2eproto, file_level_service_descriptors_plant_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_plant_2eproto_getter() {
  return &descriptor_table_plant_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_plant_2eproto(&descriptor_table_plant_2eproto);
namespace wanderer {
namespace proto {

// ===================================================================

class Plant::_Internal {
 public:
  using HasBits = decltype(std::declval<Plant>()._has_bits_);
  static void set_has_current_growth(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
  static void set_has_rate(HasBits* has_bits) {
    (*has_bits)[0] |= 2u;
  }
  static void set_has_base_y(HasBits* has_bits) {
    (*has_bits)[0] |= 4u;
  }
  static void set_has_tile_height(HasBits* has_bits) {
    (*has_bits)[0] |= 8u;
  }
  static void set_has_index(HasBits* has_bits) {
    (*has_bits)[0] |= 16u;
  }
};

Plant::Plant(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned),
  tiles_(arena),
  tall_tiles_(arena) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:wanderer.proto.Plant)
}
Plant::Plant(const Plant& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _has_bits_(from._has_bits_),
      tiles_(from.tiles_),
      tall_tiles_(from.tall_tiles_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::memcpy(&current_growth_, &from.current_growth_,
    static_cast<size_t>(reinterpret_cast<char*>(&index_) -
    reinterpret_cast<char*>(&current_growth_)) + sizeof(index_));
  // @@protoc_insertion_point(copy_constructor:wanderer.proto.Plant)
}

void Plant::SharedCtor() {
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&current_growth_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&index_) -
    reinterpret_cast<char*>(&current_growth_)) + sizeof(index_));
}

Plant::~Plant() {
  // @@protoc_insertion_point(destructor:wanderer.proto.Plant)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void Plant::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void Plant::ArenaDtor(void* object) {
  Plant* _this = reinterpret_cast< Plant* >(object);
  (void)_this;
}
void Plant::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void Plant::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void Plant::Clear() {
// @@protoc_insertion_point(message_clear_start:wanderer.proto.Plant)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  tiles_.Clear();
  tall_tiles_.Clear();
  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x0000001fu) {
    ::memset(&current_growth_, 0, static_cast<size_t>(
        reinterpret_cast<char*>(&index_) -
        reinterpret_cast<char*>(&current_growth_)) + sizeof(index_));
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Plant::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // optional float current_growth = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 13)) {
          _Internal::set_has_current_growth(&has_bits);
          current_growth_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
        } else
          goto handle_unusual;
        continue;
      // optional float rate = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 21)) {
          _Internal::set_has_rate(&has_bits);
          rate_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
        } else
          goto handle_unusual;
        continue;
      // optional float base_y = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 29)) {
          _Internal::set_has_base_y(&has_bits);
          base_y_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
        } else
          goto handle_unusual;
        continue;
      // optional int32 tile_height = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 32)) {
          _Internal::set_has_tile_height(&has_bits);
          tile_height_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // optional uint64 index = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 40)) {
          _Internal::set_has_index(&has_bits);
          index_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // repeated int32 tiles = 6 [packed = true];
      case 6:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 50)) {
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::PackedInt32Parser(_internal_mutable_tiles(), ptr, ctx);
          CHK_(ptr);
        } else if (static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 48) {
          _internal_add_tiles(::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr));
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // repeated int32 tall_tiles = 7 [packed = true];
      case 7:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 58)) {
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::PackedInt32Parser(_internal_mutable_tall_tiles(), ptr, ctx);
          CHK_(ptr);
        } else if (static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 56) {
          _internal_add_tall_tiles(::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr));
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  _has_bits_.Or(has_bits);
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* Plant::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:wanderer.proto.Plant)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // optional float current_growth = 1;
  if (_internal_has_current_growth()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteFloatToArray(1, this->_internal_current_growth(), target);
  }

  // optional float rate = 2;
  if (_internal_has_rate()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteFloatToArray(2, this->_internal_rate(), target);
  }

  // optional float base_y = 3;
  if (_internal_has_base_y()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteFloatToArray(3, this->_internal_base_y(), target);
  }

  // optional int32 tile_height = 4;
  if (_internal_has_tile_height()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(4, this->_internal_tile_height(), target);
  }

  // optional uint64 index = 5;
  if (_internal_has_index()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt64ToArray(5, this->_internal_index(), target);
  }

  // repeated int32 tiles = 6 [packed = true];
  {
    int byte_size = _tiles_cached_byte_size_.load(std::memory_order_relaxed);
    if (byte_size > 0) {
      target = stream->WriteInt32Packed(
          6, _internal_tiles(), byte_size, target);
    }
  }

  // repeated int32 tall_tiles = 7 [packed = true];
  {
    int byte_size = _tall_tiles_cached_byte_size_.load(std::memory_order_relaxed);
    if (byte_size > 0) {
      target = stream->WriteInt32Packed(
          7, _internal_tall_tiles(), byte_size, target);
    }
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:wanderer.proto.Plant)
  return target;
}

size_t Plant::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:wanderer.proto.Plant)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated int32 tiles = 6 [packed = true];
  {
    size_t data_size = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      Int32Size(this->tiles_);
    if (data_size > 0) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
            static_cast<::PROTOBUF_NAMESPACE_ID::int32>(data_size));
    }
    int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(data_size);
    _tiles_cached_byte_size_.store(cached_size,
                                    std::memory_order_relaxed);
    total_size += data_size;
  }

  // repeated int32 tall_tiles = 7 [packed = true];
  {
    size_t data_size = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      Int32Size(this->tall_tiles_);
    if (data_size > 0) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
            static_cast<::PROTOBUF_NAMESPACE_ID::int32>(data_size));
    }
    int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(data_size);
    _tall_tiles_cached_byte_size_.store(cached_size,
                                    std::memory_order_relaxed);
    total_size += data_size;
  }

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x0000001fu) {
    // optional float current_growth = 1;
    if (cached_has_bits & 0x00000001u) {
      total_size += 1 + 4;
    }

    // optional float rate = 2;
    if (cached_has_bits & 0x00000002u) {
      total_size += 1 + 4;
    }

    // optional float base_y = 3;
    if (cached_has_bits & 0x00000004u) {
      total_size += 1 + 4;
    }

    // optional int32 tile_height = 4;
    if (cached_has_bits & 0x00000008u) {
      total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32SizePlusOne(this->_internal_tile_height());
    }

    // optional uint64 index = 5;
    if (cached_has_bits & 0x00000010u) {
      total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt64SizePlusOne(this->_internal_index());
    }

  }
  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData Plant::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    Plant::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*Plant::GetClassData() const { return &_class_data_; }

void Plant::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<Plant *>(to)->MergeFrom(
      static_cast<const Plant &>(from));
}


void Plant::MergeFrom(const Plant& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:wanderer.proto.Plant)
  GOOGLE_DCHECK_NE(&from, this);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  tiles_.MergeFrom(from.tiles_);
  tall_tiles_.MergeFrom(from.tall_tiles_);
  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 0x0000001fu) {
    if (cached_has_bits & 0x00000001u) {
      current_growth_ = from.current_growth_;
    }
    if (cached_has_bits & 0x00000002u) {
      rate_ = from.rate_;
    }
    if (cached_has_bits & 0x00000004u) {
      base_y_ = from.base_y_;
    }
    if (cached_has_bits & 0x00000008u) {
      tile_height_ = from.tile_height_;
    }
    if (cached_has_bits & 0x00000010u) {
      index_ = from.index_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void Plant::CopyFrom(const Plant& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:wanderer.proto.Plant)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Plant::IsInitialized() const {
  return true;
}

void Plant::InternalSwap(Plant* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  tiles_.InternalSwap(&other->tiles_);
  tall_tiles_.InternalSwap(&other->tall_tiles_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(Plant, index_)
      + sizeof(Plant::index_)
      - PROTOBUF_FIELD_OFFSET(Plant, current_growth_)>(
          reinterpret_cast<char*>(&current_growth_),
          reinterpret_cast<char*>(&other->current_growth_));
}

::PROTOBUF_NAMESPACE_ID::Metadata Plant::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_plant_2eproto_getter, &descriptor_table_plant_2eproto_once,
      file_level_metadata_plant_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace proto
}  // namespace wanderer
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::wanderer::proto::Plant* Arena::CreateMaybeMessage< ::wanderer::proto::Plant >(Arena* arena) {
  return Arena::CreateMessageInternal< ::wanderer::proto::Plant >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
