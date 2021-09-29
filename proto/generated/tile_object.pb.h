// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: tile_object.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_tile_5fobject_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_tile_5fobject_2eproto

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
#define PROTOBUF_INTERNAL_EXPORT_tile_5fobject_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_tile_5fobject_2eproto {
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
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_tile_5fobject_2eproto;
namespace wanderer {
namespace protobuf {
class tile_object;
struct tile_objectDefaultTypeInternal;
extern tile_objectDefaultTypeInternal _tile_object_default_instance_;
}  // namespace protobuf
}  // namespace wanderer
PROTOBUF_NAMESPACE_OPEN
template<> ::wanderer::protobuf::tile_object* Arena::CreateMaybeMessage<::wanderer::protobuf::tile_object>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace wanderer {
namespace protobuf {

// ===================================================================

class tile_object final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:wanderer.protobuf.tile_object) */ {
 public:
  inline tile_object() : tile_object(nullptr) {}
  ~tile_object() override;
  explicit constexpr tile_object(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  tile_object(const tile_object& from);
  tile_object(tile_object&& from) noexcept
    : tile_object() {
    *this = ::std::move(from);
  }

  inline tile_object& operator=(const tile_object& from) {
    CopyFrom(from);
    return *this;
  }
  inline tile_object& operator=(tile_object&& from) noexcept {
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
  static const tile_object& default_instance() {
    return *internal_default_instance();
  }
  static inline const tile_object* internal_default_instance() {
    return reinterpret_cast<const tile_object*>(
               &_tile_object_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(tile_object& a, tile_object& b) {
    a.Swap(&b);
  }
  inline void Swap(tile_object* other) {
    if (other == this) return;
    if (GetOwningArena() == other->GetOwningArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(tile_object* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline tile_object* New() const final {
    return new tile_object();
  }

  tile_object* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<tile_object>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const tile_object& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const tile_object& from);
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
  void InternalSwap(tile_object* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "wanderer.protobuf.tile_object";
  }
  protected:
  explicit tile_object(::PROTOBUF_NAMESPACE_ID::Arena* arena,
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
    kTileEntityFieldNumber = 1,
  };
  // optional uint32 tile_entity = 1;
  bool has_tile_entity() const;
  private:
  bool _internal_has_tile_entity() const;
  public:
  void clear_tile_entity();
  ::PROTOBUF_NAMESPACE_ID::uint32 tile_entity() const;
  void set_tile_entity(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_tile_entity() const;
  void _internal_set_tile_entity(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // @@protoc_insertion_point(class_scope:wanderer.protobuf.tile_object)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::uint32 tile_entity_;
  friend struct ::TableStruct_tile_5fobject_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// tile_object

// optional uint32 tile_entity = 1;
inline bool tile_object::_internal_has_tile_entity() const {
  bool value = (_has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline bool tile_object::has_tile_entity() const {
  return _internal_has_tile_entity();
}
inline void tile_object::clear_tile_entity() {
  tile_entity_ = 0u;
  _has_bits_[0] &= ~0x00000001u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 tile_object::_internal_tile_entity() const {
  return tile_entity_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 tile_object::tile_entity() const {
  // @@protoc_insertion_point(field_get:wanderer.protobuf.tile_object.tile_entity)
  return _internal_tile_entity();
}
inline void tile_object::_internal_set_tile_entity(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _has_bits_[0] |= 0x00000001u;
  tile_entity_ = value;
}
inline void tile_object::set_tile_entity(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_tile_entity(value);
  // @@protoc_insertion_point(field_set:wanderer.protobuf.tile_object.tile_entity)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace protobuf
}  // namespace wanderer

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_tile_5fobject_2eproto
