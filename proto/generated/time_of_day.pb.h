// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: time_of_day.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_time_5fof_5fday_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_time_5fof_5fday_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3018000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3018000 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
#include "color.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_time_5fof_5fday_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_time_5fof_5fday_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_time_5fof_5fday_2eproto;
namespace wanderer {
namespace proto {
class TimeOfDay;
struct TimeOfDayDefaultTypeInternal;
extern TimeOfDayDefaultTypeInternal _TimeOfDay_default_instance_;
}  // namespace proto
}  // namespace wanderer
PROTOBUF_NAMESPACE_OPEN
template<> ::wanderer::proto::TimeOfDay* Arena::CreateMaybeMessage<::wanderer::proto::TimeOfDay>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace wanderer {
namespace proto {

enum DayOfWeek : int {
  MONDAY = 0,
  TUESDAY = 1,
  WEDNESDAY = 2,
  THURSDAY = 3,
  FRIDAY = 4,
  SATURDAY = 5,
  SUNDAY = 6,
  DayOfWeek_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  DayOfWeek_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool DayOfWeek_IsValid(int value);
constexpr DayOfWeek DayOfWeek_MIN = MONDAY;
constexpr DayOfWeek DayOfWeek_MAX = SUNDAY;
constexpr int DayOfWeek_ARRAYSIZE = DayOfWeek_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* DayOfWeek_descriptor();
template<typename T>
inline const std::string& DayOfWeek_Name(T enum_t_value) {
  static_assert(::std::is_same<T, DayOfWeek>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function DayOfWeek_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    DayOfWeek_descriptor(), enum_t_value);
}
inline bool DayOfWeek_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, DayOfWeek* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<DayOfWeek>(
    DayOfWeek_descriptor(), name, value);
}
// ===================================================================

class TimeOfDay final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:wanderer.proto.TimeOfDay) */ {
 public:
  inline TimeOfDay() : TimeOfDay(nullptr) {}
  ~TimeOfDay() override;
  explicit constexpr TimeOfDay(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  TimeOfDay(const TimeOfDay& from);
  TimeOfDay(TimeOfDay&& from) noexcept
    : TimeOfDay() {
    *this = ::std::move(from);
  }

  inline TimeOfDay& operator=(const TimeOfDay& from) {
    CopyFrom(from);
    return *this;
  }
  inline TimeOfDay& operator=(TimeOfDay&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const TimeOfDay& default_instance() {
    return *internal_default_instance();
  }
  static inline const TimeOfDay* internal_default_instance() {
    return reinterpret_cast<const TimeOfDay*>(
               &_TimeOfDay_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(TimeOfDay& a, TimeOfDay& b) {
    a.Swap(&b);
  }
  inline void Swap(TimeOfDay* other) {
    if (other == this) return;
    if (GetOwningArena() == other->GetOwningArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(TimeOfDay* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline TimeOfDay* New() const final {
    return new TimeOfDay();
  }

  TimeOfDay* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<TimeOfDay>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const TimeOfDay& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const TimeOfDay& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to, const ::PROTOBUF_NAMESPACE_ID::Message& from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(TimeOfDay* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "wanderer.proto.TimeOfDay";
  }
  protected:
  explicit TimeOfDay(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kTintFieldNumber = 6,
    kHourFieldNumber = 1,
    kMinuteFieldNumber = 2,
    kSecondsFieldNumber = 3,
    kWeekFieldNumber = 4,
    kDayFieldNumber = 5,
  };
  // optional .wanderer.proto.Color tint = 6;
  bool has_tint() const;
  private:
  bool _internal_has_tint() const;
  public:
  void clear_tint();
  const ::wanderer::proto::Color& tint() const;
  PROTOBUF_MUST_USE_RESULT ::wanderer::proto::Color* release_tint();
  ::wanderer::proto::Color* mutable_tint();
  void set_allocated_tint(::wanderer::proto::Color* tint);
  private:
  const ::wanderer::proto::Color& _internal_tint() const;
  ::wanderer::proto::Color* _internal_mutable_tint();
  public:
  void unsafe_arena_set_allocated_tint(
      ::wanderer::proto::Color* tint);
  ::wanderer::proto::Color* unsafe_arena_release_tint();

  // optional float hour = 1;
  bool has_hour() const;
  private:
  bool _internal_has_hour() const;
  public:
  void clear_hour();
  float hour() const;
  void set_hour(float value);
  private:
  float _internal_hour() const;
  void _internal_set_hour(float value);
  public:

  // optional float minute = 2;
  bool has_minute() const;
  private:
  bool _internal_has_minute() const;
  public:
  void clear_minute();
  float minute() const;
  void set_minute(float value);
  private:
  float _internal_minute() const;
  void _internal_set_minute(float value);
  public:

  // optional float seconds = 3;
  bool has_seconds() const;
  private:
  bool _internal_has_seconds() const;
  public:
  void clear_seconds();
  float seconds() const;
  void set_seconds(float value);
  private:
  float _internal_seconds() const;
  void _internal_set_seconds(float value);
  public:

  // optional int32 week = 4;
  bool has_week() const;
  private:
  bool _internal_has_week() const;
  public:
  void clear_week();
  ::PROTOBUF_NAMESPACE_ID::int32 week() const;
  void set_week(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_week() const;
  void _internal_set_week(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // optional .wanderer.proto.DayOfWeek day = 5;
  bool has_day() const;
  private:
  bool _internal_has_day() const;
  public:
  void clear_day();
  ::wanderer::proto::DayOfWeek day() const;
  void set_day(::wanderer::proto::DayOfWeek value);
  private:
  ::wanderer::proto::DayOfWeek _internal_day() const;
  void _internal_set_day(::wanderer::proto::DayOfWeek value);
  public:

  // @@protoc_insertion_point(class_scope:wanderer.proto.TimeOfDay)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::wanderer::proto::Color* tint_;
  float hour_;
  float minute_;
  float seconds_;
  ::PROTOBUF_NAMESPACE_ID::int32 week_;
  int day_;
  friend struct ::TableStruct_time_5fof_5fday_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// TimeOfDay

// optional float hour = 1;
inline bool TimeOfDay::_internal_has_hour() const {
  bool value = (_has_bits_[0] & 0x00000002u) != 0;
  return value;
}
inline bool TimeOfDay::has_hour() const {
  return _internal_has_hour();
}
inline void TimeOfDay::clear_hour() {
  hour_ = 0;
  _has_bits_[0] &= ~0x00000002u;
}
inline float TimeOfDay::_internal_hour() const {
  return hour_;
}
inline float TimeOfDay::hour() const {
  // @@protoc_insertion_point(field_get:wanderer.proto.TimeOfDay.hour)
  return _internal_hour();
}
inline void TimeOfDay::_internal_set_hour(float value) {
  _has_bits_[0] |= 0x00000002u;
  hour_ = value;
}
inline void TimeOfDay::set_hour(float value) {
  _internal_set_hour(value);
  // @@protoc_insertion_point(field_set:wanderer.proto.TimeOfDay.hour)
}

// optional float minute = 2;
inline bool TimeOfDay::_internal_has_minute() const {
  bool value = (_has_bits_[0] & 0x00000004u) != 0;
  return value;
}
inline bool TimeOfDay::has_minute() const {
  return _internal_has_minute();
}
inline void TimeOfDay::clear_minute() {
  minute_ = 0;
  _has_bits_[0] &= ~0x00000004u;
}
inline float TimeOfDay::_internal_minute() const {
  return minute_;
}
inline float TimeOfDay::minute() const {
  // @@protoc_insertion_point(field_get:wanderer.proto.TimeOfDay.minute)
  return _internal_minute();
}
inline void TimeOfDay::_internal_set_minute(float value) {
  _has_bits_[0] |= 0x00000004u;
  minute_ = value;
}
inline void TimeOfDay::set_minute(float value) {
  _internal_set_minute(value);
  // @@protoc_insertion_point(field_set:wanderer.proto.TimeOfDay.minute)
}

// optional float seconds = 3;
inline bool TimeOfDay::_internal_has_seconds() const {
  bool value = (_has_bits_[0] & 0x00000008u) != 0;
  return value;
}
inline bool TimeOfDay::has_seconds() const {
  return _internal_has_seconds();
}
inline void TimeOfDay::clear_seconds() {
  seconds_ = 0;
  _has_bits_[0] &= ~0x00000008u;
}
inline float TimeOfDay::_internal_seconds() const {
  return seconds_;
}
inline float TimeOfDay::seconds() const {
  // @@protoc_insertion_point(field_get:wanderer.proto.TimeOfDay.seconds)
  return _internal_seconds();
}
inline void TimeOfDay::_internal_set_seconds(float value) {
  _has_bits_[0] |= 0x00000008u;
  seconds_ = value;
}
inline void TimeOfDay::set_seconds(float value) {
  _internal_set_seconds(value);
  // @@protoc_insertion_point(field_set:wanderer.proto.TimeOfDay.seconds)
}

// optional int32 week = 4;
inline bool TimeOfDay::_internal_has_week() const {
  bool value = (_has_bits_[0] & 0x00000010u) != 0;
  return value;
}
inline bool TimeOfDay::has_week() const {
  return _internal_has_week();
}
inline void TimeOfDay::clear_week() {
  week_ = 0;
  _has_bits_[0] &= ~0x00000010u;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 TimeOfDay::_internal_week() const {
  return week_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 TimeOfDay::week() const {
  // @@protoc_insertion_point(field_get:wanderer.proto.TimeOfDay.week)
  return _internal_week();
}
inline void TimeOfDay::_internal_set_week(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _has_bits_[0] |= 0x00000010u;
  week_ = value;
}
inline void TimeOfDay::set_week(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_week(value);
  // @@protoc_insertion_point(field_set:wanderer.proto.TimeOfDay.week)
}

// optional .wanderer.proto.DayOfWeek day = 5;
inline bool TimeOfDay::_internal_has_day() const {
  bool value = (_has_bits_[0] & 0x00000020u) != 0;
  return value;
}
inline bool TimeOfDay::has_day() const {
  return _internal_has_day();
}
inline void TimeOfDay::clear_day() {
  day_ = 0;
  _has_bits_[0] &= ~0x00000020u;
}
inline ::wanderer::proto::DayOfWeek TimeOfDay::_internal_day() const {
  return static_cast< ::wanderer::proto::DayOfWeek >(day_);
}
inline ::wanderer::proto::DayOfWeek TimeOfDay::day() const {
  // @@protoc_insertion_point(field_get:wanderer.proto.TimeOfDay.day)
  return _internal_day();
}
inline void TimeOfDay::_internal_set_day(::wanderer::proto::DayOfWeek value) {
  _has_bits_[0] |= 0x00000020u;
  day_ = value;
}
inline void TimeOfDay::set_day(::wanderer::proto::DayOfWeek value) {
  _internal_set_day(value);
  // @@protoc_insertion_point(field_set:wanderer.proto.TimeOfDay.day)
}

// optional .wanderer.proto.Color tint = 6;
inline bool TimeOfDay::_internal_has_tint() const {
  bool value = (_has_bits_[0] & 0x00000001u) != 0;
  PROTOBUF_ASSUME(!value || tint_ != nullptr);
  return value;
}
inline bool TimeOfDay::has_tint() const {
  return _internal_has_tint();
}
inline const ::wanderer::proto::Color& TimeOfDay::_internal_tint() const {
  const ::wanderer::proto::Color* p = tint_;
  return p != nullptr ? *p : reinterpret_cast<const ::wanderer::proto::Color&>(
      ::wanderer::proto::_Color_default_instance_);
}
inline const ::wanderer::proto::Color& TimeOfDay::tint() const {
  // @@protoc_insertion_point(field_get:wanderer.proto.TimeOfDay.tint)
  return _internal_tint();
}
inline void TimeOfDay::unsafe_arena_set_allocated_tint(
    ::wanderer::proto::Color* tint) {
  if (GetArenaForAllocation() == nullptr) {
    delete reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(tint_);
  }
  tint_ = tint;
  if (tint) {
    _has_bits_[0] |= 0x00000001u;
  } else {
    _has_bits_[0] &= ~0x00000001u;
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:wanderer.proto.TimeOfDay.tint)
}
inline ::wanderer::proto::Color* TimeOfDay::release_tint() {
  _has_bits_[0] &= ~0x00000001u;
  ::wanderer::proto::Color* temp = tint_;
  tint_ = nullptr;
#ifdef PROTOBUF_FORCE_COPY_IN_RELEASE
  auto* old =  reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(temp);
  temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  if (GetArenaForAllocation() == nullptr) { delete old; }
#else  // PROTOBUF_FORCE_COPY_IN_RELEASE
  if (GetArenaForAllocation() != nullptr) {
    temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  }
#endif  // !PROTOBUF_FORCE_COPY_IN_RELEASE
  return temp;
}
inline ::wanderer::proto::Color* TimeOfDay::unsafe_arena_release_tint() {
  // @@protoc_insertion_point(field_release:wanderer.proto.TimeOfDay.tint)
  _has_bits_[0] &= ~0x00000001u;
  ::wanderer::proto::Color* temp = tint_;
  tint_ = nullptr;
  return temp;
}
inline ::wanderer::proto::Color* TimeOfDay::_internal_mutable_tint() {
  _has_bits_[0] |= 0x00000001u;
  if (tint_ == nullptr) {
    auto* p = CreateMaybeMessage<::wanderer::proto::Color>(GetArenaForAllocation());
    tint_ = p;
  }
  return tint_;
}
inline ::wanderer::proto::Color* TimeOfDay::mutable_tint() {
  ::wanderer::proto::Color* _msg = _internal_mutable_tint();
  // @@protoc_insertion_point(field_mutable:wanderer.proto.TimeOfDay.tint)
  return _msg;
}
inline void TimeOfDay::set_allocated_tint(::wanderer::proto::Color* tint) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaForAllocation();
  if (message_arena == nullptr) {
    delete reinterpret_cast< ::PROTOBUF_NAMESPACE_ID::MessageLite*>(tint_);
  }
  if (tint) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
        ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper<
            ::PROTOBUF_NAMESPACE_ID::MessageLite>::GetOwningArena(
                reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(tint));
    if (message_arena != submessage_arena) {
      tint = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, tint, submessage_arena);
    }
    _has_bits_[0] |= 0x00000001u;
  } else {
    _has_bits_[0] &= ~0x00000001u;
  }
  tint_ = tint;
  // @@protoc_insertion_point(field_set_allocated:wanderer.proto.TimeOfDay.tint)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace proto
}  // namespace wanderer

PROTOBUF_NAMESPACE_OPEN

template <> struct is_proto_enum< ::wanderer::proto::DayOfWeek> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::wanderer::proto::DayOfWeek>() {
  return ::wanderer::proto::DayOfWeek_descriptor();
}

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_time_5fof_5fday_2eproto
