// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: tile_layer.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_tile_5flayer_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_tile_5flayer_2eproto

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
#define PROTOBUF_INTERNAL_EXPORT_tile_5flayer_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_tile_5flayer_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[3]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_tile_5flayer_2eproto;
namespace wanderer {
namespace proto {
class TileLayer;
struct TileLayerDefaultTypeInternal;
extern TileLayerDefaultTypeInternal _TileLayer_default_instance_;
class TileMatrix;
struct TileMatrixDefaultTypeInternal;
extern TileMatrixDefaultTypeInternal _TileMatrix_default_instance_;
class TileRow;
struct TileRowDefaultTypeInternal;
extern TileRowDefaultTypeInternal _TileRow_default_instance_;
}  // namespace proto
}  // namespace wanderer
PROTOBUF_NAMESPACE_OPEN
template<> ::wanderer::proto::TileLayer* Arena::CreateMaybeMessage<::wanderer::proto::TileLayer>(Arena*);
template<> ::wanderer::proto::TileMatrix* Arena::CreateMaybeMessage<::wanderer::proto::TileMatrix>(Arena*);
template<> ::wanderer::proto::TileRow* Arena::CreateMaybeMessage<::wanderer::proto::TileRow>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace wanderer {
namespace proto {

// ===================================================================

class TileRow final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:wanderer.proto.TileRow) */ {
 public:
  inline TileRow() : TileRow(nullptr) {}
  ~TileRow() override;
  explicit constexpr TileRow(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  TileRow(const TileRow& from);
  TileRow(TileRow&& from) noexcept
    : TileRow() {
    *this = ::std::move(from);
  }

  inline TileRow& operator=(const TileRow& from) {
    CopyFrom(from);
    return *this;
  }
  inline TileRow& operator=(TileRow&& from) noexcept {
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
  static const TileRow& default_instance() {
    return *internal_default_instance();
  }
  static inline const TileRow* internal_default_instance() {
    return reinterpret_cast<const TileRow*>(
               &_TileRow_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(TileRow& a, TileRow& b) {
    a.Swap(&b);
  }
  inline void Swap(TileRow* other) {
    if (other == this) return;
    if (GetOwningArena() == other->GetOwningArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(TileRow* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline TileRow* New() const final {
    return new TileRow();
  }

  TileRow* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<TileRow>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const TileRow& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const TileRow& from);
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
  void InternalSwap(TileRow* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "wanderer.proto.TileRow";
  }
  protected:
  explicit TileRow(::PROTOBUF_NAMESPACE_ID::Arena* arena,
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
    kTilesFieldNumber = 1,
  };
  // repeated uint32 tiles = 1 [packed = true];
  int tiles_size() const;
  private:
  int _internal_tiles_size() const;
  public:
  void clear_tiles();
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_tiles(int index) const;
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >&
      _internal_tiles() const;
  void _internal_add_tiles(::PROTOBUF_NAMESPACE_ID::uint32 value);
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >*
      _internal_mutable_tiles();
  public:
  ::PROTOBUF_NAMESPACE_ID::uint32 tiles(int index) const;
  void set_tiles(int index, ::PROTOBUF_NAMESPACE_ID::uint32 value);
  void add_tiles(::PROTOBUF_NAMESPACE_ID::uint32 value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >&
      tiles() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >*
      mutable_tiles();

  // @@protoc_insertion_point(class_scope:wanderer.proto.TileRow)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 > tiles_;
  mutable std::atomic<int> _tiles_cached_byte_size_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_tile_5flayer_2eproto;
};
// -------------------------------------------------------------------

class TileMatrix final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:wanderer.proto.TileMatrix) */ {
 public:
  inline TileMatrix() : TileMatrix(nullptr) {}
  ~TileMatrix() override;
  explicit constexpr TileMatrix(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  TileMatrix(const TileMatrix& from);
  TileMatrix(TileMatrix&& from) noexcept
    : TileMatrix() {
    *this = ::std::move(from);
  }

  inline TileMatrix& operator=(const TileMatrix& from) {
    CopyFrom(from);
    return *this;
  }
  inline TileMatrix& operator=(TileMatrix&& from) noexcept {
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
  static const TileMatrix& default_instance() {
    return *internal_default_instance();
  }
  static inline const TileMatrix* internal_default_instance() {
    return reinterpret_cast<const TileMatrix*>(
               &_TileMatrix_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(TileMatrix& a, TileMatrix& b) {
    a.Swap(&b);
  }
  inline void Swap(TileMatrix* other) {
    if (other == this) return;
    if (GetOwningArena() == other->GetOwningArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(TileMatrix* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline TileMatrix* New() const final {
    return new TileMatrix();
  }

  TileMatrix* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<TileMatrix>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const TileMatrix& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const TileMatrix& from);
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
  void InternalSwap(TileMatrix* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "wanderer.proto.TileMatrix";
  }
  protected:
  explicit TileMatrix(::PROTOBUF_NAMESPACE_ID::Arena* arena,
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
    kRowsFieldNumber = 2,
  };
  // repeated .wanderer.proto.TileRow rows = 2;
  int rows_size() const;
  private:
  int _internal_rows_size() const;
  public:
  void clear_rows();
  ::wanderer::proto::TileRow* mutable_rows(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::wanderer::proto::TileRow >*
      mutable_rows();
  private:
  const ::wanderer::proto::TileRow& _internal_rows(int index) const;
  ::wanderer::proto::TileRow* _internal_add_rows();
  public:
  const ::wanderer::proto::TileRow& rows(int index) const;
  ::wanderer::proto::TileRow* add_rows();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::wanderer::proto::TileRow >&
      rows() const;

  // @@protoc_insertion_point(class_scope:wanderer.proto.TileMatrix)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::wanderer::proto::TileRow > rows_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_tile_5flayer_2eproto;
};
// -------------------------------------------------------------------

class TileLayer final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:wanderer.proto.TileLayer) */ {
 public:
  inline TileLayer() : TileLayer(nullptr) {}
  ~TileLayer() override;
  explicit constexpr TileLayer(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  TileLayer(const TileLayer& from);
  TileLayer(TileLayer&& from) noexcept
    : TileLayer() {
    *this = ::std::move(from);
  }

  inline TileLayer& operator=(const TileLayer& from) {
    CopyFrom(from);
    return *this;
  }
  inline TileLayer& operator=(TileLayer&& from) noexcept {
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
  static const TileLayer& default_instance() {
    return *internal_default_instance();
  }
  static inline const TileLayer* internal_default_instance() {
    return reinterpret_cast<const TileLayer*>(
               &_TileLayer_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  friend void swap(TileLayer& a, TileLayer& b) {
    a.Swap(&b);
  }
  inline void Swap(TileLayer* other) {
    if (other == this) return;
    if (GetOwningArena() == other->GetOwningArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(TileLayer* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline TileLayer* New() const final {
    return new TileLayer();
  }

  TileLayer* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<TileLayer>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const TileLayer& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const TileLayer& from);
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
  void InternalSwap(TileLayer* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "wanderer.proto.TileLayer";
  }
  protected:
  explicit TileLayer(::PROTOBUF_NAMESPACE_ID::Arena* arena,
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
    kMatrixFieldNumber = 1,
    kZIndexFieldNumber = 2,
  };
  // optional .wanderer.proto.TileMatrix matrix = 1;
  bool has_matrix() const;
  private:
  bool _internal_has_matrix() const;
  public:
  void clear_matrix();
  const ::wanderer::proto::TileMatrix& matrix() const;
  PROTOBUF_MUST_USE_RESULT ::wanderer::proto::TileMatrix* release_matrix();
  ::wanderer::proto::TileMatrix* mutable_matrix();
  void set_allocated_matrix(::wanderer::proto::TileMatrix* matrix);
  private:
  const ::wanderer::proto::TileMatrix& _internal_matrix() const;
  ::wanderer::proto::TileMatrix* _internal_mutable_matrix();
  public:
  void unsafe_arena_set_allocated_matrix(
      ::wanderer::proto::TileMatrix* matrix);
  ::wanderer::proto::TileMatrix* unsafe_arena_release_matrix();

  // optional int32 z_index = 2;
  bool has_z_index() const;
  private:
  bool _internal_has_z_index() const;
  public:
  void clear_z_index();
  ::PROTOBUF_NAMESPACE_ID::int32 z_index() const;
  void set_z_index(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_z_index() const;
  void _internal_set_z_index(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // @@protoc_insertion_point(class_scope:wanderer.proto.TileLayer)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::wanderer::proto::TileMatrix* matrix_;
  ::PROTOBUF_NAMESPACE_ID::int32 z_index_;
  friend struct ::TableStruct_tile_5flayer_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// TileRow

// repeated uint32 tiles = 1 [packed = true];
inline int TileRow::_internal_tiles_size() const {
  return tiles_.size();
}
inline int TileRow::tiles_size() const {
  return _internal_tiles_size();
}
inline void TileRow::clear_tiles() {
  tiles_.Clear();
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 TileRow::_internal_tiles(int index) const {
  return tiles_.Get(index);
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 TileRow::tiles(int index) const {
  // @@protoc_insertion_point(field_get:wanderer.proto.TileRow.tiles)
  return _internal_tiles(index);
}
inline void TileRow::set_tiles(int index, ::PROTOBUF_NAMESPACE_ID::uint32 value) {
  tiles_.Set(index, value);
  // @@protoc_insertion_point(field_set:wanderer.proto.TileRow.tiles)
}
inline void TileRow::_internal_add_tiles(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  tiles_.Add(value);
}
inline void TileRow::add_tiles(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_add_tiles(value);
  // @@protoc_insertion_point(field_add:wanderer.proto.TileRow.tiles)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >&
TileRow::_internal_tiles() const {
  return tiles_;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >&
TileRow::tiles() const {
  // @@protoc_insertion_point(field_list:wanderer.proto.TileRow.tiles)
  return _internal_tiles();
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >*
TileRow::_internal_mutable_tiles() {
  return &tiles_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >*
TileRow::mutable_tiles() {
  // @@protoc_insertion_point(field_mutable_list:wanderer.proto.TileRow.tiles)
  return _internal_mutable_tiles();
}

// -------------------------------------------------------------------

// TileMatrix

// repeated .wanderer.proto.TileRow rows = 2;
inline int TileMatrix::_internal_rows_size() const {
  return rows_.size();
}
inline int TileMatrix::rows_size() const {
  return _internal_rows_size();
}
inline void TileMatrix::clear_rows() {
  rows_.Clear();
}
inline ::wanderer::proto::TileRow* TileMatrix::mutable_rows(int index) {
  // @@protoc_insertion_point(field_mutable:wanderer.proto.TileMatrix.rows)
  return rows_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::wanderer::proto::TileRow >*
TileMatrix::mutable_rows() {
  // @@protoc_insertion_point(field_mutable_list:wanderer.proto.TileMatrix.rows)
  return &rows_;
}
inline const ::wanderer::proto::TileRow& TileMatrix::_internal_rows(int index) const {
  return rows_.Get(index);
}
inline const ::wanderer::proto::TileRow& TileMatrix::rows(int index) const {
  // @@protoc_insertion_point(field_get:wanderer.proto.TileMatrix.rows)
  return _internal_rows(index);
}
inline ::wanderer::proto::TileRow* TileMatrix::_internal_add_rows() {
  return rows_.Add();
}
inline ::wanderer::proto::TileRow* TileMatrix::add_rows() {
  ::wanderer::proto::TileRow* _add = _internal_add_rows();
  // @@protoc_insertion_point(field_add:wanderer.proto.TileMatrix.rows)
  return _add;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::wanderer::proto::TileRow >&
TileMatrix::rows() const {
  // @@protoc_insertion_point(field_list:wanderer.proto.TileMatrix.rows)
  return rows_;
}

// -------------------------------------------------------------------

// TileLayer

// optional .wanderer.proto.TileMatrix matrix = 1;
inline bool TileLayer::_internal_has_matrix() const {
  bool value = (_has_bits_[0] & 0x00000001u) != 0;
  PROTOBUF_ASSUME(!value || matrix_ != nullptr);
  return value;
}
inline bool TileLayer::has_matrix() const {
  return _internal_has_matrix();
}
inline void TileLayer::clear_matrix() {
  if (matrix_ != nullptr) matrix_->Clear();
  _has_bits_[0] &= ~0x00000001u;
}
inline const ::wanderer::proto::TileMatrix& TileLayer::_internal_matrix() const {
  const ::wanderer::proto::TileMatrix* p = matrix_;
  return p != nullptr ? *p : reinterpret_cast<const ::wanderer::proto::TileMatrix&>(
      ::wanderer::proto::_TileMatrix_default_instance_);
}
inline const ::wanderer::proto::TileMatrix& TileLayer::matrix() const {
  // @@protoc_insertion_point(field_get:wanderer.proto.TileLayer.matrix)
  return _internal_matrix();
}
inline void TileLayer::unsafe_arena_set_allocated_matrix(
    ::wanderer::proto::TileMatrix* matrix) {
  if (GetArenaForAllocation() == nullptr) {
    delete reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(matrix_);
  }
  matrix_ = matrix;
  if (matrix) {
    _has_bits_[0] |= 0x00000001u;
  } else {
    _has_bits_[0] &= ~0x00000001u;
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:wanderer.proto.TileLayer.matrix)
}
inline ::wanderer::proto::TileMatrix* TileLayer::release_matrix() {
  _has_bits_[0] &= ~0x00000001u;
  ::wanderer::proto::TileMatrix* temp = matrix_;
  matrix_ = nullptr;
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
inline ::wanderer::proto::TileMatrix* TileLayer::unsafe_arena_release_matrix() {
  // @@protoc_insertion_point(field_release:wanderer.proto.TileLayer.matrix)
  _has_bits_[0] &= ~0x00000001u;
  ::wanderer::proto::TileMatrix* temp = matrix_;
  matrix_ = nullptr;
  return temp;
}
inline ::wanderer::proto::TileMatrix* TileLayer::_internal_mutable_matrix() {
  _has_bits_[0] |= 0x00000001u;
  if (matrix_ == nullptr) {
    auto* p = CreateMaybeMessage<::wanderer::proto::TileMatrix>(GetArenaForAllocation());
    matrix_ = p;
  }
  return matrix_;
}
inline ::wanderer::proto::TileMatrix* TileLayer::mutable_matrix() {
  ::wanderer::proto::TileMatrix* _msg = _internal_mutable_matrix();
  // @@protoc_insertion_point(field_mutable:wanderer.proto.TileLayer.matrix)
  return _msg;
}
inline void TileLayer::set_allocated_matrix(::wanderer::proto::TileMatrix* matrix) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaForAllocation();
  if (message_arena == nullptr) {
    delete matrix_;
  }
  if (matrix) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
        ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper<::wanderer::proto::TileMatrix>::GetOwningArena(matrix);
    if (message_arena != submessage_arena) {
      matrix = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, matrix, submessage_arena);
    }
    _has_bits_[0] |= 0x00000001u;
  } else {
    _has_bits_[0] &= ~0x00000001u;
  }
  matrix_ = matrix;
  // @@protoc_insertion_point(field_set_allocated:wanderer.proto.TileLayer.matrix)
}

// optional int32 z_index = 2;
inline bool TileLayer::_internal_has_z_index() const {
  bool value = (_has_bits_[0] & 0x00000002u) != 0;
  return value;
}
inline bool TileLayer::has_z_index() const {
  return _internal_has_z_index();
}
inline void TileLayer::clear_z_index() {
  z_index_ = 0;
  _has_bits_[0] &= ~0x00000002u;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 TileLayer::_internal_z_index() const {
  return z_index_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 TileLayer::z_index() const {
  // @@protoc_insertion_point(field_get:wanderer.proto.TileLayer.z_index)
  return _internal_z_index();
}
inline void TileLayer::_internal_set_z_index(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _has_bits_[0] |= 0x00000002u;
  z_index_ = value;
}
inline void TileLayer::set_z_index(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_z_index(value);
  // @@protoc_insertion_point(field_set:wanderer.proto.TileLayer.z_index)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace proto
}  // namespace wanderer

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_tile_5flayer_2eproto
