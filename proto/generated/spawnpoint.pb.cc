// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: spawnpoint.proto

#include "spawnpoint.pb.h"

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
constexpr spawnpoint::spawnpoint(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : position_(nullptr)
  , type_(0)
{}
struct spawnpointDefaultTypeInternal {
  constexpr spawnpointDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~spawnpointDefaultTypeInternal() {}
  union {
    spawnpoint _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT spawnpointDefaultTypeInternal _spawnpoint_default_instance_;
}  // namespace proto
}  // namespace wanderer
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_spawnpoint_2eproto[1];
static const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* file_level_enum_descriptors_spawnpoint_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_spawnpoint_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_spawnpoint_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::spawnpoint, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::spawnpoint, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::spawnpoint, type_),
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::spawnpoint, position_),
  1,
  0,
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 8, -1, sizeof(::wanderer::proto::spawnpoint)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::wanderer::proto::_spawnpoint_default_instance_),
};

const char descriptor_table_protodef_spawnpoint_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\020spawnpoint.proto\022\016wanderer.proto\032\014floa"
  "t2.proto\"\205\001\n\nspawnpoint\0222\n\004type\030\001 \001(\0162\037."
  "wanderer.proto.spawnpoint_typeH\000\210\001\001\022-\n\010p"
  "osition\030\002 \001(\0132\026.wanderer.proto.float2H\001\210"
  "\001\001B\007\n\005_typeB\013\n\t_position*+\n\017spawnpoint_t"
  "ype\022\n\n\006PLAYER\020\000\022\014\n\010SKELETON\020\001b\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_spawnpoint_2eproto_deps[1] = {
  &::descriptor_table_float2_2eproto,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_spawnpoint_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_spawnpoint_2eproto = {
  false, false, 237, descriptor_table_protodef_spawnpoint_2eproto, "spawnpoint.proto", 
  &descriptor_table_spawnpoint_2eproto_once, descriptor_table_spawnpoint_2eproto_deps, 1, 1,
  schemas, file_default_instances, TableStruct_spawnpoint_2eproto::offsets,
  file_level_metadata_spawnpoint_2eproto, file_level_enum_descriptors_spawnpoint_2eproto, file_level_service_descriptors_spawnpoint_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_spawnpoint_2eproto_getter() {
  return &descriptor_table_spawnpoint_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_spawnpoint_2eproto(&descriptor_table_spawnpoint_2eproto);
namespace wanderer {
namespace proto {
const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* spawnpoint_type_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_spawnpoint_2eproto);
  return file_level_enum_descriptors_spawnpoint_2eproto[0];
}
bool spawnpoint_type_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
      return true;
    default:
      return false;
  }
}


// ===================================================================

class spawnpoint::_Internal {
 public:
  using HasBits = decltype(std::declval<spawnpoint>()._has_bits_);
  static void set_has_type(HasBits* has_bits) {
    (*has_bits)[0] |= 2u;
  }
  static const ::wanderer::proto::float2& position(const spawnpoint* msg);
  static void set_has_position(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
};

const ::wanderer::proto::float2&
spawnpoint::_Internal::position(const spawnpoint* msg) {
  return *msg->position_;
}
void spawnpoint::clear_position() {
  if (position_ != nullptr) position_->Clear();
  _has_bits_[0] &= ~0x00000001u;
}
spawnpoint::spawnpoint(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:wanderer.proto.spawnpoint)
}
spawnpoint::spawnpoint(const spawnpoint& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  if (from._internal_has_position()) {
    position_ = new ::wanderer::proto::float2(*from.position_);
  } else {
    position_ = nullptr;
  }
  type_ = from.type_;
  // @@protoc_insertion_point(copy_constructor:wanderer.proto.spawnpoint)
}

void spawnpoint::SharedCtor() {
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&position_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&type_) -
    reinterpret_cast<char*>(&position_)) + sizeof(type_));
}

spawnpoint::~spawnpoint() {
  // @@protoc_insertion_point(destructor:wanderer.proto.spawnpoint)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void spawnpoint::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  if (this != internal_default_instance()) delete position_;
}

void spawnpoint::ArenaDtor(void* object) {
  spawnpoint* _this = reinterpret_cast< spawnpoint* >(object);
  (void)_this;
}
void spawnpoint::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void spawnpoint::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void spawnpoint::Clear() {
// @@protoc_insertion_point(message_clear_start:wanderer.proto.spawnpoint)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    GOOGLE_DCHECK(position_ != nullptr);
    position_->Clear();
  }
  type_ = 0;
  _has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* spawnpoint::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // optional .wanderer.proto.spawnpoint_type type = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          ::PROTOBUF_NAMESPACE_ID::uint64 val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          _internal_set_type(static_cast<::wanderer::proto::spawnpoint_type>(val));
        } else
          goto handle_unusual;
        continue;
      // optional .wanderer.proto.float2 position = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          ptr = ctx->ParseMessage(_internal_mutable_position(), ptr);
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

::PROTOBUF_NAMESPACE_ID::uint8* spawnpoint::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:wanderer.proto.spawnpoint)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // optional .wanderer.proto.spawnpoint_type type = 1;
  if (_internal_has_type()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnumToArray(
      1, this->_internal_type(), target);
  }

  // optional .wanderer.proto.float2 position = 2;
  if (_internal_has_position()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        2, _Internal::position(this), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:wanderer.proto.spawnpoint)
  return target;
}

size_t spawnpoint::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:wanderer.proto.spawnpoint)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    // optional .wanderer.proto.float2 position = 2;
    if (cached_has_bits & 0x00000001u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
          *position_);
    }

    // optional .wanderer.proto.spawnpoint_type type = 1;
    if (cached_has_bits & 0x00000002u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->_internal_type());
    }

  }
  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData spawnpoint::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    spawnpoint::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*spawnpoint::GetClassData() const { return &_class_data_; }

void spawnpoint::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<spawnpoint *>(to)->MergeFrom(
      static_cast<const spawnpoint &>(from));
}


void spawnpoint::MergeFrom(const spawnpoint& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:wanderer.proto.spawnpoint)
  GOOGLE_DCHECK_NE(&from, this);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    if (cached_has_bits & 0x00000001u) {
      _internal_mutable_position()->::wanderer::proto::float2::MergeFrom(from._internal_position());
    }
    if (cached_has_bits & 0x00000002u) {
      type_ = from.type_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void spawnpoint::CopyFrom(const spawnpoint& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:wanderer.proto.spawnpoint)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool spawnpoint::IsInitialized() const {
  return true;
}

void spawnpoint::InternalSwap(spawnpoint* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(spawnpoint, type_)
      + sizeof(spawnpoint::type_)
      - PROTOBUF_FIELD_OFFSET(spawnpoint, position_)>(
          reinterpret_cast<char*>(&position_),
          reinterpret_cast<char*>(&other->position_));
}

::PROTOBUF_NAMESPACE_ID::Metadata spawnpoint::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_spawnpoint_2eproto_getter, &descriptor_table_spawnpoint_2eproto_once,
      file_level_metadata_spawnpoint_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace proto
}  // namespace wanderer
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::wanderer::proto::spawnpoint* Arena::CreateMaybeMessage< ::wanderer::proto::spawnpoint >(Arena* arena) {
  return Arena::CreateMessageInternal< ::wanderer::proto::spawnpoint >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>