// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: tileset.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_tileset_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_tileset_2eproto

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
#include <google/protobuf/map.h>  // IWYU pragma: export
#include <google/protobuf/map_entry.h>
#include <google/protobuf/map_field_inl.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_tileset_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_tileset_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[2]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_tileset_2eproto;
namespace wanderer {
namespace proto {
class Tileset;
struct TilesetDefaultTypeInternal;
extern TilesetDefaultTypeInternal _Tileset_default_instance_;
class Tileset_TileToEntityEntry_DoNotUse;
struct Tileset_TileToEntityEntry_DoNotUseDefaultTypeInternal;
extern Tileset_TileToEntityEntry_DoNotUseDefaultTypeInternal _Tileset_TileToEntityEntry_DoNotUse_default_instance_;
}  // namespace proto
}  // namespace wanderer
PROTOBUF_NAMESPACE_OPEN
template<> ::wanderer::proto::Tileset* Arena::CreateMaybeMessage<::wanderer::proto::Tileset>(Arena*);
template<> ::wanderer::proto::Tileset_TileToEntityEntry_DoNotUse* Arena::CreateMaybeMessage<::wanderer::proto::Tileset_TileToEntityEntry_DoNotUse>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace wanderer {
namespace proto {

// ===================================================================

class Tileset_TileToEntityEntry_DoNotUse : public ::PROTOBUF_NAMESPACE_ID::internal::MapEntry<Tileset_TileToEntityEntry_DoNotUse, 
    ::PROTOBUF_NAMESPACE_ID::int32, ::PROTOBUF_NAMESPACE_ID::uint32,
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_INT32,
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_UINT32> {
public:
  typedef ::PROTOBUF_NAMESPACE_ID::internal::MapEntry<Tileset_TileToEntityEntry_DoNotUse, 
    ::PROTOBUF_NAMESPACE_ID::int32, ::PROTOBUF_NAMESPACE_ID::uint32,
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_INT32,
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_UINT32> SuperType;
  Tileset_TileToEntityEntry_DoNotUse();
  explicit constexpr Tileset_TileToEntityEntry_DoNotUse(
      ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);
  explicit Tileset_TileToEntityEntry_DoNotUse(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  void MergeFrom(const Tileset_TileToEntityEntry_DoNotUse& other);
  static const Tileset_TileToEntityEntry_DoNotUse* internal_default_instance() { return reinterpret_cast<const Tileset_TileToEntityEntry_DoNotUse*>(&_Tileset_TileToEntityEntry_DoNotUse_default_instance_); }
  static bool ValidateKey(void*) { return true; }
  static bool ValidateValue(void*) { return true; }
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
};

// -------------------------------------------------------------------

class Tileset final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:wanderer.proto.Tileset) */ {
 public:
  inline Tileset() : Tileset(nullptr) {}
  ~Tileset() override;
  explicit constexpr Tileset(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Tileset(const Tileset& from);
  Tileset(Tileset&& from) noexcept
    : Tileset() {
    *this = ::std::move(from);
  }

  inline Tileset& operator=(const Tileset& from) {
    CopyFrom(from);
    return *this;
  }
  inline Tileset& operator=(Tileset&& from) noexcept {
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
  static const Tileset& default_instance() {
    return *internal_default_instance();
  }
  static inline const Tileset* internal_default_instance() {
    return reinterpret_cast<const Tileset*>(
               &_Tileset_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(Tileset& a, Tileset& b) {
    a.Swap(&b);
  }
  inline void Swap(Tileset* other) {
    if (other == this) return;
    if (GetOwningArena() == other->GetOwningArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Tileset* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline Tileset* New() const final {
    return new Tileset();
  }

  Tileset* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Tileset>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const Tileset& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const Tileset& from);
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
  void InternalSwap(Tileset* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "wanderer.proto.Tileset";
  }
  protected:
  explicit Tileset(::PROTOBUF_NAMESPACE_ID::Arena* arena,
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
    kTileToEntityFieldNumber = 1,
  };
  // map<int32, uint32> tile_to_entity = 1;
  int tile_to_entity_size() const;
  private:
  int _internal_tile_to_entity_size() const;
  public:
  void clear_tile_to_entity();
  private:
  const ::PROTOBUF_NAMESPACE_ID::Map< ::PROTOBUF_NAMESPACE_ID::int32, ::PROTOBUF_NAMESPACE_ID::uint32 >&
      _internal_tile_to_entity() const;
  ::PROTOBUF_NAMESPACE_ID::Map< ::PROTOBUF_NAMESPACE_ID::int32, ::PROTOBUF_NAMESPACE_ID::uint32 >*
      _internal_mutable_tile_to_entity();
  public:
  const ::PROTOBUF_NAMESPACE_ID::Map< ::PROTOBUF_NAMESPACE_ID::int32, ::PROTOBUF_NAMESPACE_ID::uint32 >&
      tile_to_entity() const;
  ::PROTOBUF_NAMESPACE_ID::Map< ::PROTOBUF_NAMESPACE_ID::int32, ::PROTOBUF_NAMESPACE_ID::uint32 >*
      mutable_tile_to_entity();

  // @@protoc_insertion_point(class_scope:wanderer.proto.Tileset)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::MapField<
      Tileset_TileToEntityEntry_DoNotUse,
      ::PROTOBUF_NAMESPACE_ID::int32, ::PROTOBUF_NAMESPACE_ID::uint32,
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_INT32,
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_UINT32> tile_to_entity_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_tileset_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// Tileset

// map<int32, uint32> tile_to_entity = 1;
inline int Tileset::_internal_tile_to_entity_size() const {
  return tile_to_entity_.size();
}
inline int Tileset::tile_to_entity_size() const {
  return _internal_tile_to_entity_size();
}
inline void Tileset::clear_tile_to_entity() {
  tile_to_entity_.Clear();
}
inline const ::PROTOBUF_NAMESPACE_ID::Map< ::PROTOBUF_NAMESPACE_ID::int32, ::PROTOBUF_NAMESPACE_ID::uint32 >&
Tileset::_internal_tile_to_entity() const {
  return tile_to_entity_.GetMap();
}
inline const ::PROTOBUF_NAMESPACE_ID::Map< ::PROTOBUF_NAMESPACE_ID::int32, ::PROTOBUF_NAMESPACE_ID::uint32 >&
Tileset::tile_to_entity() const {
  // @@protoc_insertion_point(field_map:wanderer.proto.Tileset.tile_to_entity)
  return _internal_tile_to_entity();
}
inline ::PROTOBUF_NAMESPACE_ID::Map< ::PROTOBUF_NAMESPACE_ID::int32, ::PROTOBUF_NAMESPACE_ID::uint32 >*
Tileset::_internal_mutable_tile_to_entity() {
  return tile_to_entity_.MutableMap();
}
inline ::PROTOBUF_NAMESPACE_ID::Map< ::PROTOBUF_NAMESPACE_ID::int32, ::PROTOBUF_NAMESPACE_ID::uint32 >*
Tileset::mutable_tile_to_entity() {
  // @@protoc_insertion_point(field_mutable_map:wanderer.proto.Tileset.tile_to_entity)
  return _internal_mutable_tile_to_entity();
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace proto
}  // namespace wanderer

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_tileset_2eproto
