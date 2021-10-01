// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: inventory.proto

#include "inventory.pb.h"

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
constexpr inventory::inventory(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : items_()
  , _items_cached_byte_size_(0)
  , capacity_(uint64_t{0u}){}
struct inventoryDefaultTypeInternal {
  constexpr inventoryDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~inventoryDefaultTypeInternal() {}
  union {
    inventory _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT inventoryDefaultTypeInternal _inventory_default_instance_;
}  // namespace proto
}  // namespace wanderer
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_inventory_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_inventory_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_inventory_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_inventory_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::inventory, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::inventory, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::inventory, items_),
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::inventory, capacity_),
  ~0u,
  0,
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 8, -1, sizeof(::wanderer::proto::inventory)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::wanderer::proto::_inventory_default_instance_),
};

const char descriptor_table_protodef_inventory_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\017inventory.proto\022\016wanderer.proto\"B\n\tinv"
  "entory\022\021\n\005items\030\001 \003(\rB\002\020\001\022\025\n\010capacity\030\002 "
  "\001(\004H\000\210\001\001B\013\n\t_capacityb\006proto3"
  ;
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_inventory_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_inventory_2eproto = {
  false, false, 109, descriptor_table_protodef_inventory_2eproto, "inventory.proto", 
  &descriptor_table_inventory_2eproto_once, nullptr, 0, 1,
  schemas, file_default_instances, TableStruct_inventory_2eproto::offsets,
  file_level_metadata_inventory_2eproto, file_level_enum_descriptors_inventory_2eproto, file_level_service_descriptors_inventory_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_inventory_2eproto_getter() {
  return &descriptor_table_inventory_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_inventory_2eproto(&descriptor_table_inventory_2eproto);
namespace wanderer {
namespace proto {

// ===================================================================

class inventory::_Internal {
 public:
  using HasBits = decltype(std::declval<inventory>()._has_bits_);
  static void set_has_capacity(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
};

inventory::inventory(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned),
  items_(arena) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:wanderer.proto.inventory)
}
inventory::inventory(const inventory& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _has_bits_(from._has_bits_),
      items_(from.items_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  capacity_ = from.capacity_;
  // @@protoc_insertion_point(copy_constructor:wanderer.proto.inventory)
}

void inventory::SharedCtor() {
capacity_ = uint64_t{0u};
}

inventory::~inventory() {
  // @@protoc_insertion_point(destructor:wanderer.proto.inventory)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void inventory::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void inventory::ArenaDtor(void* object) {
  inventory* _this = reinterpret_cast< inventory* >(object);
  (void)_this;
}
void inventory::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void inventory::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void inventory::Clear() {
// @@protoc_insertion_point(message_clear_start:wanderer.proto.inventory)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  items_.Clear();
  capacity_ = uint64_t{0u};
  _has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* inventory::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // repeated uint32 items = 1 [packed = true];
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::PackedUInt32Parser(_internal_mutable_items(), ptr, ctx);
          CHK_(ptr);
        } else if (static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8) {
          _internal_add_items(::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr));
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // optional uint64 capacity = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          _Internal::set_has_capacity(&has_bits);
          capacity_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
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

::PROTOBUF_NAMESPACE_ID::uint8* inventory::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:wanderer.proto.inventory)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated uint32 items = 1 [packed = true];
  {
    int byte_size = _items_cached_byte_size_.load(std::memory_order_relaxed);
    if (byte_size > 0) {
      target = stream->WriteUInt32Packed(
          1, _internal_items(), byte_size, target);
    }
  }

  // optional uint64 capacity = 2;
  if (_internal_has_capacity()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt64ToArray(2, this->_internal_capacity(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:wanderer.proto.inventory)
  return target;
}

size_t inventory::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:wanderer.proto.inventory)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated uint32 items = 1 [packed = true];
  {
    size_t data_size = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      UInt32Size(this->items_);
    if (data_size > 0) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
            static_cast<::PROTOBUF_NAMESPACE_ID::int32>(data_size));
    }
    int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(data_size);
    _items_cached_byte_size_.store(cached_size,
                                    std::memory_order_relaxed);
    total_size += data_size;
  }

  // optional uint64 capacity = 2;
  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt64SizePlusOne(this->_internal_capacity());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData inventory::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    inventory::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*inventory::GetClassData() const { return &_class_data_; }

void inventory::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<inventory *>(to)->MergeFrom(
      static_cast<const inventory &>(from));
}


void inventory::MergeFrom(const inventory& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:wanderer.proto.inventory)
  GOOGLE_DCHECK_NE(&from, this);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  items_.MergeFrom(from.items_);
  if (from._internal_has_capacity()) {
    _internal_set_capacity(from._internal_capacity());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void inventory::CopyFrom(const inventory& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:wanderer.proto.inventory)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool inventory::IsInitialized() const {
  return true;
}

void inventory::InternalSwap(inventory* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  items_.InternalSwap(&other->items_);
  swap(capacity_, other->capacity_);
}

::PROTOBUF_NAMESPACE_ID::Metadata inventory::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_inventory_2eproto_getter, &descriptor_table_inventory_2eproto_once,
      file_level_metadata_inventory_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace proto
}  // namespace wanderer
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::wanderer::proto::inventory* Arena::CreateMaybeMessage< ::wanderer::proto::inventory >(Arena* arena) {
  return Arena::CreateMessageInternal< ::wanderer::proto::inventory >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
