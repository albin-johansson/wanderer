// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: color.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_color_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_color_2eproto

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
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_color_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_color_2eproto {
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
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_color_2eproto;
namespace wanderer {
namespace protobuf {
class color;
struct colorDefaultTypeInternal;
extern colorDefaultTypeInternal _color_default_instance_;
}  // namespace protobuf
}  // namespace wanderer
PROTOBUF_NAMESPACE_OPEN
template<> ::wanderer::protobuf::color* Arena::CreateMaybeMessage<::wanderer::protobuf::color>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace wanderer {
namespace protobuf {

// ===================================================================

class color final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:wanderer.protobuf.color) */ {
 public:
  inline color() : color(nullptr) {}
  ~color() override;
  explicit constexpr color(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  color(const color& from);
  color(color&& from) noexcept
    : color() {
    *this = ::std::move(from);
  }

  inline color& operator=(const color& from) {
    CopyFrom(from);
    return *this;
  }
  inline color& operator=(color&& from) noexcept {
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
  static const color& default_instance() {
    return *internal_default_instance();
  }
  static inline const color* internal_default_instance() {
    return reinterpret_cast<const color*>(
               &_color_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(color& a, color& b) {
    a.Swap(&b);
  }
  inline void Swap(color* other) {
    if (other == this) return;
    if (GetOwningArena() == other->GetOwningArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(color* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline color* New() const final {
    return new color();
  }

  color* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<color>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const color& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const color& from);
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
  void InternalSwap(color* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "wanderer.protobuf.color";
  }
  protected:
  explicit color(::PROTOBUF_NAMESPACE_ID::Arena* arena,
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
    kRedFieldNumber = 1,
    kGreenFieldNumber = 2,
    kBlueFieldNumber = 3,
    kAlphaFieldNumber = 4,
  };
  // optional uint32 red = 1;
  bool has_red() const;
  private:
  bool _internal_has_red() const;
  public:
  void clear_red();
  ::PROTOBUF_NAMESPACE_ID::uint32 red() const;
  void set_red(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_red() const;
  void _internal_set_red(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // optional uint32 green = 2;
  bool has_green() const;
  private:
  bool _internal_has_green() const;
  public:
  void clear_green();
  ::PROTOBUF_NAMESPACE_ID::uint32 green() const;
  void set_green(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_green() const;
  void _internal_set_green(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // optional uint32 blue = 3;
  bool has_blue() const;
  private:
  bool _internal_has_blue() const;
  public:
  void clear_blue();
  ::PROTOBUF_NAMESPACE_ID::uint32 blue() const;
  void set_blue(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_blue() const;
  void _internal_set_blue(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // optional uint32 alpha = 4;
  bool has_alpha() const;
  private:
  bool _internal_has_alpha() const;
  public:
  void clear_alpha();
  ::PROTOBUF_NAMESPACE_ID::uint32 alpha() const;
  void set_alpha(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_alpha() const;
  void _internal_set_alpha(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // @@protoc_insertion_point(class_scope:wanderer.protobuf.color)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::uint32 red_;
  ::PROTOBUF_NAMESPACE_ID::uint32 green_;
  ::PROTOBUF_NAMESPACE_ID::uint32 blue_;
  ::PROTOBUF_NAMESPACE_ID::uint32 alpha_;
  friend struct ::TableStruct_color_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// color

// optional uint32 red = 1;
inline bool color::_internal_has_red() const {
  bool value = (_has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline bool color::has_red() const {
  return _internal_has_red();
}
inline void color::clear_red() {
  red_ = 0u;
  _has_bits_[0] &= ~0x00000001u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 color::_internal_red() const {
  return red_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 color::red() const {
  // @@protoc_insertion_point(field_get:wanderer.protobuf.color.red)
  return _internal_red();
}
inline void color::_internal_set_red(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _has_bits_[0] |= 0x00000001u;
  red_ = value;
}
inline void color::set_red(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_red(value);
  // @@protoc_insertion_point(field_set:wanderer.protobuf.color.red)
}

// optional uint32 green = 2;
inline bool color::_internal_has_green() const {
  bool value = (_has_bits_[0] & 0x00000002u) != 0;
  return value;
}
inline bool color::has_green() const {
  return _internal_has_green();
}
inline void color::clear_green() {
  green_ = 0u;
  _has_bits_[0] &= ~0x00000002u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 color::_internal_green() const {
  return green_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 color::green() const {
  // @@protoc_insertion_point(field_get:wanderer.protobuf.color.green)
  return _internal_green();
}
inline void color::_internal_set_green(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _has_bits_[0] |= 0x00000002u;
  green_ = value;
}
inline void color::set_green(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_green(value);
  // @@protoc_insertion_point(field_set:wanderer.protobuf.color.green)
}

// optional uint32 blue = 3;
inline bool color::_internal_has_blue() const {
  bool value = (_has_bits_[0] & 0x00000004u) != 0;
  return value;
}
inline bool color::has_blue() const {
  return _internal_has_blue();
}
inline void color::clear_blue() {
  blue_ = 0u;
  _has_bits_[0] &= ~0x00000004u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 color::_internal_blue() const {
  return blue_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 color::blue() const {
  // @@protoc_insertion_point(field_get:wanderer.protobuf.color.blue)
  return _internal_blue();
}
inline void color::_internal_set_blue(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _has_bits_[0] |= 0x00000004u;
  blue_ = value;
}
inline void color::set_blue(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_blue(value);
  // @@protoc_insertion_point(field_set:wanderer.protobuf.color.blue)
}

// optional uint32 alpha = 4;
inline bool color::_internal_has_alpha() const {
  bool value = (_has_bits_[0] & 0x00000008u) != 0;
  return value;
}
inline bool color::has_alpha() const {
  return _internal_has_alpha();
}
inline void color::clear_alpha() {
  alpha_ = 0u;
  _has_bits_[0] &= ~0x00000008u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 color::_internal_alpha() const {
  return alpha_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 color::alpha() const {
  // @@protoc_insertion_point(field_get:wanderer.protobuf.color.alpha)
  return _internal_alpha();
}
inline void color::_internal_set_alpha(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _has_bits_[0] |= 0x00000008u;
  alpha_ = value;
}
inline void color::set_alpha(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_alpha(value);
  // @@protoc_insertion_point(field_set:wanderer.protobuf.color.alpha)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace protobuf
}  // namespace wanderer

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_color_2eproto
