// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: time_of_day.proto

#include "time_of_day.pb.h"

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
constexpr time_of_day::time_of_day(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : tint_(nullptr)
  , hour_(0)
  , minute_(0)
  , seconds_(0)
  , week_(0)
  , day_(0)
{}
struct time_of_dayDefaultTypeInternal {
  constexpr time_of_dayDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~time_of_dayDefaultTypeInternal() {}
  union {
    time_of_day _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT time_of_dayDefaultTypeInternal _time_of_day_default_instance_;
}  // namespace proto
}  // namespace wanderer
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_time_5fof_5fday_2eproto[1];
static const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* file_level_enum_descriptors_time_5fof_5fday_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_time_5fof_5fday_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_time_5fof_5fday_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::time_of_day, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::time_of_day, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::time_of_day, hour_),
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::time_of_day, minute_),
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::time_of_day, seconds_),
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::time_of_day, week_),
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::time_of_day, day_),
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::time_of_day, tint_),
  1,
  2,
  3,
  4,
  5,
  0,
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 12, -1, sizeof(::wanderer::proto::time_of_day)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::wanderer::proto::_time_of_day_default_instance_),
};

const char descriptor_table_protodef_time_5fof_5fday_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\021time_of_day.proto\022\016wanderer.proto\032\013col"
  "or.proto\"\361\001\n\013time_of_day\022\021\n\004hour\030\001 \001(\002H\000"
  "\210\001\001\022\023\n\006minute\030\002 \001(\002H\001\210\001\001\022\024\n\007seconds\030\003 \001("
  "\002H\002\210\001\001\022\021\n\004week\030\004 \001(\005H\003\210\001\001\022-\n\003day\030\005 \001(\0162\033"
  ".wanderer.proto.day_of_weekH\004\210\001\001\022(\n\004tint"
  "\030\006 \001(\0132\025.wanderer.proto.colorH\005\210\001\001B\007\n\005_h"
  "ourB\t\n\007_minuteB\n\n\010_secondsB\007\n\005_weekB\006\n\004_"
  "dayB\007\n\005_tint*i\n\013day_of_week\022\n\n\006MONDAY\020\000\022"
  "\013\n\007TUESDAY\020\001\022\r\n\tWEDNESDAY\020\002\022\014\n\010THURSDAY\020"
  "\003\022\n\n\006FRIDAY\020\004\022\014\n\010SATURDAY\020\005\022\n\n\006SUNDAY\020\006b"
  "\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_time_5fof_5fday_2eproto_deps[1] = {
  &::descriptor_table_color_2eproto,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_time_5fof_5fday_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_time_5fof_5fday_2eproto = {
  false, false, 407, descriptor_table_protodef_time_5fof_5fday_2eproto, "time_of_day.proto", 
  &descriptor_table_time_5fof_5fday_2eproto_once, descriptor_table_time_5fof_5fday_2eproto_deps, 1, 1,
  schemas, file_default_instances, TableStruct_time_5fof_5fday_2eproto::offsets,
  file_level_metadata_time_5fof_5fday_2eproto, file_level_enum_descriptors_time_5fof_5fday_2eproto, file_level_service_descriptors_time_5fof_5fday_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_time_5fof_5fday_2eproto_getter() {
  return &descriptor_table_time_5fof_5fday_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_time_5fof_5fday_2eproto(&descriptor_table_time_5fof_5fday_2eproto);
namespace wanderer {
namespace proto {
const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* day_of_week_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_time_5fof_5fday_2eproto);
  return file_level_enum_descriptors_time_5fof_5fday_2eproto[0];
}
bool day_of_week_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
      return true;
    default:
      return false;
  }
}


// ===================================================================

class time_of_day::_Internal {
 public:
  using HasBits = decltype(std::declval<time_of_day>()._has_bits_);
  static void set_has_hour(HasBits* has_bits) {
    (*has_bits)[0] |= 2u;
  }
  static void set_has_minute(HasBits* has_bits) {
    (*has_bits)[0] |= 4u;
  }
  static void set_has_seconds(HasBits* has_bits) {
    (*has_bits)[0] |= 8u;
  }
  static void set_has_week(HasBits* has_bits) {
    (*has_bits)[0] |= 16u;
  }
  static void set_has_day(HasBits* has_bits) {
    (*has_bits)[0] |= 32u;
  }
  static const ::wanderer::proto::color& tint(const time_of_day* msg);
  static void set_has_tint(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
};

const ::wanderer::proto::color&
time_of_day::_Internal::tint(const time_of_day* msg) {
  return *msg->tint_;
}
void time_of_day::clear_tint() {
  if (tint_ != nullptr) tint_->Clear();
  _has_bits_[0] &= ~0x00000001u;
}
time_of_day::time_of_day(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:wanderer.proto.time_of_day)
}
time_of_day::time_of_day(const time_of_day& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  if (from._internal_has_tint()) {
    tint_ = new ::wanderer::proto::color(*from.tint_);
  } else {
    tint_ = nullptr;
  }
  ::memcpy(&hour_, &from.hour_,
    static_cast<size_t>(reinterpret_cast<char*>(&day_) -
    reinterpret_cast<char*>(&hour_)) + sizeof(day_));
  // @@protoc_insertion_point(copy_constructor:wanderer.proto.time_of_day)
}

void time_of_day::SharedCtor() {
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&tint_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&day_) -
    reinterpret_cast<char*>(&tint_)) + sizeof(day_));
}

time_of_day::~time_of_day() {
  // @@protoc_insertion_point(destructor:wanderer.proto.time_of_day)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void time_of_day::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  if (this != internal_default_instance()) delete tint_;
}

void time_of_day::ArenaDtor(void* object) {
  time_of_day* _this = reinterpret_cast< time_of_day* >(object);
  (void)_this;
}
void time_of_day::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void time_of_day::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void time_of_day::Clear() {
// @@protoc_insertion_point(message_clear_start:wanderer.proto.time_of_day)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    GOOGLE_DCHECK(tint_ != nullptr);
    tint_->Clear();
  }
  if (cached_has_bits & 0x0000003eu) {
    ::memset(&hour_, 0, static_cast<size_t>(
        reinterpret_cast<char*>(&day_) -
        reinterpret_cast<char*>(&hour_)) + sizeof(day_));
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* time_of_day::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // optional float hour = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 13)) {
          _Internal::set_has_hour(&has_bits);
          hour_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
        } else
          goto handle_unusual;
        continue;
      // optional float minute = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 21)) {
          _Internal::set_has_minute(&has_bits);
          minute_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
        } else
          goto handle_unusual;
        continue;
      // optional float seconds = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 29)) {
          _Internal::set_has_seconds(&has_bits);
          seconds_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
        } else
          goto handle_unusual;
        continue;
      // optional int32 week = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 32)) {
          _Internal::set_has_week(&has_bits);
          week_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // optional .wanderer.proto.day_of_week day = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 40)) {
          ::PROTOBUF_NAMESPACE_ID::uint64 val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          _internal_set_day(static_cast<::wanderer::proto::day_of_week>(val));
        } else
          goto handle_unusual;
        continue;
      // optional .wanderer.proto.color tint = 6;
      case 6:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 50)) {
          ptr = ctx->ParseMessage(_internal_mutable_tint(), ptr);
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

::PROTOBUF_NAMESPACE_ID::uint8* time_of_day::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:wanderer.proto.time_of_day)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // optional float hour = 1;
  if (_internal_has_hour()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteFloatToArray(1, this->_internal_hour(), target);
  }

  // optional float minute = 2;
  if (_internal_has_minute()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteFloatToArray(2, this->_internal_minute(), target);
  }

  // optional float seconds = 3;
  if (_internal_has_seconds()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteFloatToArray(3, this->_internal_seconds(), target);
  }

  // optional int32 week = 4;
  if (_internal_has_week()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(4, this->_internal_week(), target);
  }

  // optional .wanderer.proto.day_of_week day = 5;
  if (_internal_has_day()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnumToArray(
      5, this->_internal_day(), target);
  }

  // optional .wanderer.proto.color tint = 6;
  if (_internal_has_tint()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        6, _Internal::tint(this), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:wanderer.proto.time_of_day)
  return target;
}

size_t time_of_day::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:wanderer.proto.time_of_day)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x0000003fu) {
    // optional .wanderer.proto.color tint = 6;
    if (cached_has_bits & 0x00000001u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
          *tint_);
    }

    // optional float hour = 1;
    if (cached_has_bits & 0x00000002u) {
      total_size += 1 + 4;
    }

    // optional float minute = 2;
    if (cached_has_bits & 0x00000004u) {
      total_size += 1 + 4;
    }

    // optional float seconds = 3;
    if (cached_has_bits & 0x00000008u) {
      total_size += 1 + 4;
    }

    // optional int32 week = 4;
    if (cached_has_bits & 0x00000010u) {
      total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32SizePlusOne(this->_internal_week());
    }

    // optional .wanderer.proto.day_of_week day = 5;
    if (cached_has_bits & 0x00000020u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->_internal_day());
    }

  }
  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData time_of_day::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    time_of_day::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*time_of_day::GetClassData() const { return &_class_data_; }

void time_of_day::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<time_of_day *>(to)->MergeFrom(
      static_cast<const time_of_day &>(from));
}


void time_of_day::MergeFrom(const time_of_day& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:wanderer.proto.time_of_day)
  GOOGLE_DCHECK_NE(&from, this);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 0x0000003fu) {
    if (cached_has_bits & 0x00000001u) {
      _internal_mutable_tint()->::wanderer::proto::color::MergeFrom(from._internal_tint());
    }
    if (cached_has_bits & 0x00000002u) {
      hour_ = from.hour_;
    }
    if (cached_has_bits & 0x00000004u) {
      minute_ = from.minute_;
    }
    if (cached_has_bits & 0x00000008u) {
      seconds_ = from.seconds_;
    }
    if (cached_has_bits & 0x00000010u) {
      week_ = from.week_;
    }
    if (cached_has_bits & 0x00000020u) {
      day_ = from.day_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void time_of_day::CopyFrom(const time_of_day& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:wanderer.proto.time_of_day)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool time_of_day::IsInitialized() const {
  return true;
}

void time_of_day::InternalSwap(time_of_day* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(time_of_day, day_)
      + sizeof(time_of_day::day_)
      - PROTOBUF_FIELD_OFFSET(time_of_day, tint_)>(
          reinterpret_cast<char*>(&tint_),
          reinterpret_cast<char*>(&other->tint_));
}

::PROTOBUF_NAMESPACE_ID::Metadata time_of_day::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_time_5fof_5fday_2eproto_getter, &descriptor_table_time_5fof_5fday_2eproto_once,
      file_level_metadata_time_5fof_5fday_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace proto
}  // namespace wanderer
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::wanderer::proto::time_of_day* Arena::CreateMaybeMessage< ::wanderer::proto::time_of_day >(Arena* arena) {
  return Arena::CreateMessageInternal< ::wanderer::proto::time_of_day >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
