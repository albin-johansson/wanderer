// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: point_light.proto

#include "point_light.pb.h"

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
constexpr PointLight::PointLight(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : position_(nullptr)
  , size_(0)
  , fluctuation_(0)
  , fluctuation_step_(0)
  , fluctuation_limit_(0){}
struct PointLightDefaultTypeInternal {
  constexpr PointLightDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~PointLightDefaultTypeInternal() {}
  union {
    PointLight _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PointLightDefaultTypeInternal _PointLight_default_instance_;
}  // namespace proto
}  // namespace wanderer
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_point_5flight_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_point_5flight_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_point_5flight_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_point_5flight_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::PointLight, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::PointLight, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::PointLight, position_),
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::PointLight, size_),
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::PointLight, fluctuation_),
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::PointLight, fluctuation_step_),
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::PointLight, fluctuation_limit_),
  0,
  1,
  2,
  3,
  4,
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 11, -1, sizeof(::wanderer::proto::PointLight)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::wanderer::proto::_PointLight_default_instance_),
};

const char descriptor_table_protodef_point_5flight_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\021point_light.proto\022\016wanderer.proto\032\014flo"
  "at2.proto\"\370\001\n\nPointLight\022-\n\010position\030\001 \001"
  "(\0132\026.wanderer.proto.float2H\000\210\001\001\022\021\n\004size\030"
  "\002 \001(\002H\001\210\001\001\022\030\n\013fluctuation\030\003 \001(\002H\002\210\001\001\022\035\n\020"
  "fluctuation_step\030\004 \001(\002H\003\210\001\001\022\036\n\021fluctuati"
  "on_limit\030\005 \001(\002H\004\210\001\001B\013\n\t_positionB\007\n\005_siz"
  "eB\016\n\014_fluctuationB\023\n\021_fluctuation_stepB\024"
  "\n\022_fluctuation_limitb\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_point_5flight_2eproto_deps[1] = {
  &::descriptor_table_float2_2eproto,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_point_5flight_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_point_5flight_2eproto = {
  false, false, 308, descriptor_table_protodef_point_5flight_2eproto, "point_light.proto", 
  &descriptor_table_point_5flight_2eproto_once, descriptor_table_point_5flight_2eproto_deps, 1, 1,
  schemas, file_default_instances, TableStruct_point_5flight_2eproto::offsets,
  file_level_metadata_point_5flight_2eproto, file_level_enum_descriptors_point_5flight_2eproto, file_level_service_descriptors_point_5flight_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_point_5flight_2eproto_getter() {
  return &descriptor_table_point_5flight_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_point_5flight_2eproto(&descriptor_table_point_5flight_2eproto);
namespace wanderer {
namespace proto {

// ===================================================================

class PointLight::_Internal {
 public:
  using HasBits = decltype(std::declval<PointLight>()._has_bits_);
  static const ::wanderer::proto::float2& position(const PointLight* msg);
  static void set_has_position(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
  static void set_has_size(HasBits* has_bits) {
    (*has_bits)[0] |= 2u;
  }
  static void set_has_fluctuation(HasBits* has_bits) {
    (*has_bits)[0] |= 4u;
  }
  static void set_has_fluctuation_step(HasBits* has_bits) {
    (*has_bits)[0] |= 8u;
  }
  static void set_has_fluctuation_limit(HasBits* has_bits) {
    (*has_bits)[0] |= 16u;
  }
};

const ::wanderer::proto::float2&
PointLight::_Internal::position(const PointLight* msg) {
  return *msg->position_;
}
void PointLight::clear_position() {
  if (position_ != nullptr) position_->Clear();
  _has_bits_[0] &= ~0x00000001u;
}
PointLight::PointLight(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:wanderer.proto.PointLight)
}
PointLight::PointLight(const PointLight& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  if (from._internal_has_position()) {
    position_ = new ::wanderer::proto::float2(*from.position_);
  } else {
    position_ = nullptr;
  }
  ::memcpy(&size_, &from.size_,
    static_cast<size_t>(reinterpret_cast<char*>(&fluctuation_limit_) -
    reinterpret_cast<char*>(&size_)) + sizeof(fluctuation_limit_));
  // @@protoc_insertion_point(copy_constructor:wanderer.proto.PointLight)
}

void PointLight::SharedCtor() {
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&position_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&fluctuation_limit_) -
    reinterpret_cast<char*>(&position_)) + sizeof(fluctuation_limit_));
}

PointLight::~PointLight() {
  // @@protoc_insertion_point(destructor:wanderer.proto.PointLight)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void PointLight::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  if (this != internal_default_instance()) delete position_;
}

void PointLight::ArenaDtor(void* object) {
  PointLight* _this = reinterpret_cast< PointLight* >(object);
  (void)_this;
}
void PointLight::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void PointLight::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void PointLight::Clear() {
// @@protoc_insertion_point(message_clear_start:wanderer.proto.PointLight)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    GOOGLE_DCHECK(position_ != nullptr);
    position_->Clear();
  }
  if (cached_has_bits & 0x0000001eu) {
    ::memset(&size_, 0, static_cast<size_t>(
        reinterpret_cast<char*>(&fluctuation_limit_) -
        reinterpret_cast<char*>(&size_)) + sizeof(fluctuation_limit_));
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* PointLight::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // optional .wanderer.proto.float2 position = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          ptr = ctx->ParseMessage(_internal_mutable_position(), ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // optional float size = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 21)) {
          _Internal::set_has_size(&has_bits);
          size_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
        } else
          goto handle_unusual;
        continue;
      // optional float fluctuation = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 29)) {
          _Internal::set_has_fluctuation(&has_bits);
          fluctuation_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
        } else
          goto handle_unusual;
        continue;
      // optional float fluctuation_step = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 37)) {
          _Internal::set_has_fluctuation_step(&has_bits);
          fluctuation_step_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
        } else
          goto handle_unusual;
        continue;
      // optional float fluctuation_limit = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 45)) {
          _Internal::set_has_fluctuation_limit(&has_bits);
          fluctuation_limit_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
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

::PROTOBUF_NAMESPACE_ID::uint8* PointLight::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:wanderer.proto.PointLight)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // optional .wanderer.proto.float2 position = 1;
  if (_internal_has_position()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        1, _Internal::position(this), target, stream);
  }

  // optional float size = 2;
  if (_internal_has_size()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteFloatToArray(2, this->_internal_size(), target);
  }

  // optional float fluctuation = 3;
  if (_internal_has_fluctuation()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteFloatToArray(3, this->_internal_fluctuation(), target);
  }

  // optional float fluctuation_step = 4;
  if (_internal_has_fluctuation_step()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteFloatToArray(4, this->_internal_fluctuation_step(), target);
  }

  // optional float fluctuation_limit = 5;
  if (_internal_has_fluctuation_limit()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteFloatToArray(5, this->_internal_fluctuation_limit(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:wanderer.proto.PointLight)
  return target;
}

size_t PointLight::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:wanderer.proto.PointLight)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x0000001fu) {
    // optional .wanderer.proto.float2 position = 1;
    if (cached_has_bits & 0x00000001u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
          *position_);
    }

    // optional float size = 2;
    if (cached_has_bits & 0x00000002u) {
      total_size += 1 + 4;
    }

    // optional float fluctuation = 3;
    if (cached_has_bits & 0x00000004u) {
      total_size += 1 + 4;
    }

    // optional float fluctuation_step = 4;
    if (cached_has_bits & 0x00000008u) {
      total_size += 1 + 4;
    }

    // optional float fluctuation_limit = 5;
    if (cached_has_bits & 0x00000010u) {
      total_size += 1 + 4;
    }

  }
  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData PointLight::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    PointLight::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*PointLight::GetClassData() const { return &_class_data_; }

void PointLight::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<PointLight *>(to)->MergeFrom(
      static_cast<const PointLight &>(from));
}


void PointLight::MergeFrom(const PointLight& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:wanderer.proto.PointLight)
  GOOGLE_DCHECK_NE(&from, this);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 0x0000001fu) {
    if (cached_has_bits & 0x00000001u) {
      _internal_mutable_position()->::wanderer::proto::float2::MergeFrom(from._internal_position());
    }
    if (cached_has_bits & 0x00000002u) {
      size_ = from.size_;
    }
    if (cached_has_bits & 0x00000004u) {
      fluctuation_ = from.fluctuation_;
    }
    if (cached_has_bits & 0x00000008u) {
      fluctuation_step_ = from.fluctuation_step_;
    }
    if (cached_has_bits & 0x00000010u) {
      fluctuation_limit_ = from.fluctuation_limit_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void PointLight::CopyFrom(const PointLight& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:wanderer.proto.PointLight)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool PointLight::IsInitialized() const {
  return true;
}

void PointLight::InternalSwap(PointLight* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(PointLight, fluctuation_limit_)
      + sizeof(PointLight::fluctuation_limit_)
      - PROTOBUF_FIELD_OFFSET(PointLight, position_)>(
          reinterpret_cast<char*>(&position_),
          reinterpret_cast<char*>(&other->position_));
}

::PROTOBUF_NAMESPACE_ID::Metadata PointLight::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_point_5flight_2eproto_getter, &descriptor_table_point_5flight_2eproto_once,
      file_level_metadata_point_5flight_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace proto
}  // namespace wanderer
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::wanderer::proto::PointLight* Arena::CreateMaybeMessage< ::wanderer::proto::PointLight >(Arena* arena) {
  return Arena::CreateMessageInternal< ::wanderer::proto::PointLight >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
