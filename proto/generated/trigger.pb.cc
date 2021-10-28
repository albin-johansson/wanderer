// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: trigger.proto

#include "trigger.pb.h"

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
constexpr Trigger::Trigger(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : type_(0)
{}
struct TriggerDefaultTypeInternal {
  constexpr TriggerDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~TriggerDefaultTypeInternal() {}
  union {
    Trigger _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT TriggerDefaultTypeInternal _Trigger_default_instance_;
}  // namespace proto
}  // namespace wanderer
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_trigger_2eproto[1];
static const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* file_level_enum_descriptors_trigger_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_trigger_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_trigger_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::Trigger, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::Trigger, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::Trigger, type_),
  0,
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 7, -1, sizeof(::wanderer::proto::Trigger)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::wanderer::proto::_Trigger_default_instance_),
};

const char descriptor_table_protodef_trigger_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\rtrigger.proto\022\016wanderer.proto\"B\n\007Trigg"
  "er\022.\n\004type\030\001 \001(\0162\033.wanderer.proto.Trigge"
  "rTypeH\000\210\001\001B\007\n\005_type*1\n\013TriggerType\022\n\n\006PO"
  "RTAL\020\000\022\r\n\tCONTAINER\020\001\022\007\n\003BED\020\002b\006proto3"
  ;
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_trigger_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_trigger_2eproto = {
  false, false, 158, descriptor_table_protodef_trigger_2eproto, "trigger.proto", 
  &descriptor_table_trigger_2eproto_once, nullptr, 0, 1,
  schemas, file_default_instances, TableStruct_trigger_2eproto::offsets,
  file_level_metadata_trigger_2eproto, file_level_enum_descriptors_trigger_2eproto, file_level_service_descriptors_trigger_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_trigger_2eproto_getter() {
  return &descriptor_table_trigger_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_trigger_2eproto(&descriptor_table_trigger_2eproto);
namespace wanderer {
namespace proto {
const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* TriggerType_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_trigger_2eproto);
  return file_level_enum_descriptors_trigger_2eproto[0];
}
bool TriggerType_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
      return true;
    default:
      return false;
  }
}


// ===================================================================

class Trigger::_Internal {
 public:
  using HasBits = decltype(std::declval<Trigger>()._has_bits_);
  static void set_has_type(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
};

Trigger::Trigger(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:wanderer.proto.Trigger)
}
Trigger::Trigger(const Trigger& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  type_ = from.type_;
  // @@protoc_insertion_point(copy_constructor:wanderer.proto.Trigger)
}

void Trigger::SharedCtor() {
type_ = 0;
}

Trigger::~Trigger() {
  // @@protoc_insertion_point(destructor:wanderer.proto.Trigger)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void Trigger::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void Trigger::ArenaDtor(void* object) {
  Trigger* _this = reinterpret_cast< Trigger* >(object);
  (void)_this;
}
void Trigger::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void Trigger::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void Trigger::Clear() {
// @@protoc_insertion_point(message_clear_start:wanderer.proto.Trigger)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  type_ = 0;
  _has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Trigger::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // optional .wanderer.proto.TriggerType type = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          ::PROTOBUF_NAMESPACE_ID::uint64 val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          _internal_set_type(static_cast<::wanderer::proto::TriggerType>(val));
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

::PROTOBUF_NAMESPACE_ID::uint8* Trigger::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:wanderer.proto.Trigger)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // optional .wanderer.proto.TriggerType type = 1;
  if (_internal_has_type()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnumToArray(
      1, this->_internal_type(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:wanderer.proto.Trigger)
  return target;
}

size_t Trigger::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:wanderer.proto.Trigger)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // optional .wanderer.proto.TriggerType type = 1;
  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->_internal_type());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData Trigger::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    Trigger::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*Trigger::GetClassData() const { return &_class_data_; }

void Trigger::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<Trigger *>(to)->MergeFrom(
      static_cast<const Trigger &>(from));
}


void Trigger::MergeFrom(const Trigger& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:wanderer.proto.Trigger)
  GOOGLE_DCHECK_NE(&from, this);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_has_type()) {
    _internal_set_type(from._internal_type());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void Trigger::CopyFrom(const Trigger& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:wanderer.proto.Trigger)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Trigger::IsInitialized() const {
  return true;
}

void Trigger::InternalSwap(Trigger* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  swap(type_, other->type_);
}

::PROTOBUF_NAMESPACE_ID::Metadata Trigger::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_trigger_2eproto_getter, &descriptor_table_trigger_2eproto_once,
      file_level_metadata_trigger_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace proto
}  // namespace wanderer
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::wanderer::proto::Trigger* Arena::CreateMaybeMessage< ::wanderer::proto::Trigger >(Arena* arena) {
  return Arena::CreateMessageInternal< ::wanderer::proto::Trigger >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
