// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: trigger.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_trigger_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_trigger_2eproto

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
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_trigger_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_trigger_2eproto {
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
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_trigger_2eproto;
namespace wanderer {
namespace proto {
class trigger;
struct triggerDefaultTypeInternal;
extern triggerDefaultTypeInternal _trigger_default_instance_;
}  // namespace proto
}  // namespace wanderer
PROTOBUF_NAMESPACE_OPEN
template<> ::wanderer::proto::trigger* Arena::CreateMaybeMessage<::wanderer::proto::trigger>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace wanderer {
namespace proto {

enum trigger_type : int {
  PORTAL = 0,
  CONTAINER = 1,
  BED = 2,
  trigger_type_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  trigger_type_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool trigger_type_IsValid(int value);
constexpr trigger_type trigger_type_MIN = PORTAL;
constexpr trigger_type trigger_type_MAX = BED;
constexpr int trigger_type_ARRAYSIZE = trigger_type_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* trigger_type_descriptor();
template<typename T>
inline const std::string& trigger_type_Name(T enum_t_value) {
  static_assert(::std::is_same<T, trigger_type>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function trigger_type_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    trigger_type_descriptor(), enum_t_value);
}
inline bool trigger_type_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, trigger_type* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<trigger_type>(
    trigger_type_descriptor(), name, value);
}
// ===================================================================

class trigger final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:wanderer.proto.trigger) */ {
 public:
  inline trigger() : trigger(nullptr) {}
  ~trigger() override;
  explicit constexpr trigger(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  trigger(const trigger& from);
  trigger(trigger&& from) noexcept
    : trigger() {
    *this = ::std::move(from);
  }

  inline trigger& operator=(const trigger& from) {
    CopyFrom(from);
    return *this;
  }
  inline trigger& operator=(trigger&& from) noexcept {
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
  static const trigger& default_instance() {
    return *internal_default_instance();
  }
  static inline const trigger* internal_default_instance() {
    return reinterpret_cast<const trigger*>(
               &_trigger_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(trigger& a, trigger& b) {
    a.Swap(&b);
  }
  inline void Swap(trigger* other) {
    if (other == this) return;
    if (GetOwningArena() == other->GetOwningArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(trigger* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline trigger* New() const final {
    return new trigger();
  }

  trigger* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<trigger>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const trigger& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const trigger& from);
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
  void InternalSwap(trigger* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "wanderer.proto.trigger";
  }
  protected:
  explicit trigger(::PROTOBUF_NAMESPACE_ID::Arena* arena,
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
    kTypeFieldNumber = 1,
  };
  // optional .wanderer.proto.trigger_type type = 1;
  bool has_type() const;
  private:
  bool _internal_has_type() const;
  public:
  void clear_type();
  ::wanderer::proto::trigger_type type() const;
  void set_type(::wanderer::proto::trigger_type value);
  private:
  ::wanderer::proto::trigger_type _internal_type() const;
  void _internal_set_type(::wanderer::proto::trigger_type value);
  public:

  // @@protoc_insertion_point(class_scope:wanderer.proto.trigger)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  int type_;
  friend struct ::TableStruct_trigger_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// trigger

// optional .wanderer.proto.trigger_type type = 1;
inline bool trigger::_internal_has_type() const {
  bool value = (_has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline bool trigger::has_type() const {
  return _internal_has_type();
}
inline void trigger::clear_type() {
  type_ = 0;
  _has_bits_[0] &= ~0x00000001u;
}
inline ::wanderer::proto::trigger_type trigger::_internal_type() const {
  return static_cast< ::wanderer::proto::trigger_type >(type_);
}
inline ::wanderer::proto::trigger_type trigger::type() const {
  // @@protoc_insertion_point(field_get:wanderer.proto.trigger.type)
  return _internal_type();
}
inline void trigger::_internal_set_type(::wanderer::proto::trigger_type value) {
  _has_bits_[0] |= 0x00000001u;
  type_ = value;
}
inline void trigger::set_type(::wanderer::proto::trigger_type value) {
  _internal_set_type(value);
  // @@protoc_insertion_point(field_set:wanderer.proto.trigger.type)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace proto
}  // namespace wanderer

PROTOBUF_NAMESPACE_OPEN

template <> struct is_proto_enum< ::wanderer::proto::trigger_type> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::wanderer::proto::trigger_type>() {
  return ::wanderer::proto::trigger_type_descriptor();
}

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_trigger_2eproto
