// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: tile_layer.proto

#include "tile_layer.pb.h"

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
constexpr tile_row::tile_row(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : tiles_()
  , _tiles_cached_byte_size_(0){}
struct tile_rowDefaultTypeInternal {
  constexpr tile_rowDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~tile_rowDefaultTypeInternal() {}
  union {
    tile_row _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT tile_rowDefaultTypeInternal _tile_row_default_instance_;
constexpr tile_matrix::tile_matrix(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : rows_(){}
struct tile_matrixDefaultTypeInternal {
  constexpr tile_matrixDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~tile_matrixDefaultTypeInternal() {}
  union {
    tile_matrix _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT tile_matrixDefaultTypeInternal _tile_matrix_default_instance_;
constexpr tile_layer::tile_layer(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : matrix_(nullptr)
  , z_index_(0){}
struct tile_layerDefaultTypeInternal {
  constexpr tile_layerDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~tile_layerDefaultTypeInternal() {}
  union {
    tile_layer _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT tile_layerDefaultTypeInternal _tile_layer_default_instance_;
}  // namespace proto
}  // namespace wanderer
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_tile_5flayer_2eproto[3];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_tile_5flayer_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_tile_5flayer_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_tile_5flayer_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::tile_row, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::tile_row, tiles_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::tile_matrix, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::tile_matrix, rows_),
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::tile_layer, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::tile_layer, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::tile_layer, matrix_),
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::tile_layer, z_index_),
  0,
  1,
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::wanderer::proto::tile_row)},
  { 7, -1, -1, sizeof(::wanderer::proto::tile_matrix)},
  { 14, 22, -1, sizeof(::wanderer::proto::tile_layer)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::wanderer::proto::_tile_row_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::wanderer::proto::_tile_matrix_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::wanderer::proto::_tile_layer_default_instance_),
};

const char descriptor_table_protodef_tile_5flayer_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\020tile_layer.proto\022\016wanderer.proto\"\035\n\010ti"
  "le_row\022\021\n\005tiles\030\001 \003(\rB\002\020\001\"5\n\013tile_matrix"
  "\022&\n\004rows\030\002 \003(\0132\030.wanderer.proto.tile_row"
  "\"k\n\ntile_layer\0220\n\006matrix\030\001 \001(\0132\033.wandere"
  "r.proto.tile_matrixH\000\210\001\001\022\024\n\007z_index\030\002 \001("
  "\005H\001\210\001\001B\t\n\007_matrixB\n\n\010_z_indexb\006proto3"
  ;
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_tile_5flayer_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_tile_5flayer_2eproto = {
  false, false, 237, descriptor_table_protodef_tile_5flayer_2eproto, "tile_layer.proto", 
  &descriptor_table_tile_5flayer_2eproto_once, nullptr, 0, 3,
  schemas, file_default_instances, TableStruct_tile_5flayer_2eproto::offsets,
  file_level_metadata_tile_5flayer_2eproto, file_level_enum_descriptors_tile_5flayer_2eproto, file_level_service_descriptors_tile_5flayer_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_tile_5flayer_2eproto_getter() {
  return &descriptor_table_tile_5flayer_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_tile_5flayer_2eproto(&descriptor_table_tile_5flayer_2eproto);
namespace wanderer {
namespace proto {

// ===================================================================

class tile_row::_Internal {
 public:
};

tile_row::tile_row(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned),
  tiles_(arena) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:wanderer.proto.tile_row)
}
tile_row::tile_row(const tile_row& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      tiles_(from.tiles_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:wanderer.proto.tile_row)
}

void tile_row::SharedCtor() {
}

tile_row::~tile_row() {
  // @@protoc_insertion_point(destructor:wanderer.proto.tile_row)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void tile_row::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void tile_row::ArenaDtor(void* object) {
  tile_row* _this = reinterpret_cast< tile_row* >(object);
  (void)_this;
}
void tile_row::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void tile_row::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void tile_row::Clear() {
// @@protoc_insertion_point(message_clear_start:wanderer.proto.tile_row)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  tiles_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* tile_row::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // repeated uint32 tiles = 1 [packed = true];
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::PackedUInt32Parser(_internal_mutable_tiles(), ptr, ctx);
          CHK_(ptr);
        } else if (static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8) {
          _internal_add_tiles(::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr));
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
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* tile_row::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:wanderer.proto.tile_row)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated uint32 tiles = 1 [packed = true];
  {
    int byte_size = _tiles_cached_byte_size_.load(std::memory_order_relaxed);
    if (byte_size > 0) {
      target = stream->WriteUInt32Packed(
          1, _internal_tiles(), byte_size, target);
    }
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:wanderer.proto.tile_row)
  return target;
}

size_t tile_row::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:wanderer.proto.tile_row)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated uint32 tiles = 1 [packed = true];
  {
    size_t data_size = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      UInt32Size(this->tiles_);
    if (data_size > 0) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
            static_cast<::PROTOBUF_NAMESPACE_ID::int32>(data_size));
    }
    int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(data_size);
    _tiles_cached_byte_size_.store(cached_size,
                                    std::memory_order_relaxed);
    total_size += data_size;
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData tile_row::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    tile_row::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*tile_row::GetClassData() const { return &_class_data_; }

void tile_row::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<tile_row *>(to)->MergeFrom(
      static_cast<const tile_row &>(from));
}


void tile_row::MergeFrom(const tile_row& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:wanderer.proto.tile_row)
  GOOGLE_DCHECK_NE(&from, this);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  tiles_.MergeFrom(from.tiles_);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void tile_row::CopyFrom(const tile_row& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:wanderer.proto.tile_row)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool tile_row::IsInitialized() const {
  return true;
}

void tile_row::InternalSwap(tile_row* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  tiles_.InternalSwap(&other->tiles_);
}

::PROTOBUF_NAMESPACE_ID::Metadata tile_row::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_tile_5flayer_2eproto_getter, &descriptor_table_tile_5flayer_2eproto_once,
      file_level_metadata_tile_5flayer_2eproto[0]);
}

// ===================================================================

class tile_matrix::_Internal {
 public:
};

tile_matrix::tile_matrix(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned),
  rows_(arena) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:wanderer.proto.tile_matrix)
}
tile_matrix::tile_matrix(const tile_matrix& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      rows_(from.rows_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:wanderer.proto.tile_matrix)
}

void tile_matrix::SharedCtor() {
}

tile_matrix::~tile_matrix() {
  // @@protoc_insertion_point(destructor:wanderer.proto.tile_matrix)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void tile_matrix::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void tile_matrix::ArenaDtor(void* object) {
  tile_matrix* _this = reinterpret_cast< tile_matrix* >(object);
  (void)_this;
}
void tile_matrix::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void tile_matrix::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void tile_matrix::Clear() {
// @@protoc_insertion_point(message_clear_start:wanderer.proto.tile_matrix)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  rows_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* tile_matrix::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // repeated .wanderer.proto.tile_row rows = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ctx->ParseMessage(_internal_add_rows(), ptr);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<18>(ptr));
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
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* tile_matrix::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:wanderer.proto.tile_matrix)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated .wanderer.proto.tile_row rows = 2;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->_internal_rows_size()); i < n; i++) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(2, this->_internal_rows(i), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:wanderer.proto.tile_matrix)
  return target;
}

size_t tile_matrix::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:wanderer.proto.tile_matrix)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated .wanderer.proto.tile_row rows = 2;
  total_size += 1UL * this->_internal_rows_size();
  for (const auto& msg : this->rows_) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData tile_matrix::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    tile_matrix::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*tile_matrix::GetClassData() const { return &_class_data_; }

void tile_matrix::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<tile_matrix *>(to)->MergeFrom(
      static_cast<const tile_matrix &>(from));
}


void tile_matrix::MergeFrom(const tile_matrix& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:wanderer.proto.tile_matrix)
  GOOGLE_DCHECK_NE(&from, this);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  rows_.MergeFrom(from.rows_);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void tile_matrix::CopyFrom(const tile_matrix& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:wanderer.proto.tile_matrix)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool tile_matrix::IsInitialized() const {
  return true;
}

void tile_matrix::InternalSwap(tile_matrix* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  rows_.InternalSwap(&other->rows_);
}

::PROTOBUF_NAMESPACE_ID::Metadata tile_matrix::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_tile_5flayer_2eproto_getter, &descriptor_table_tile_5flayer_2eproto_once,
      file_level_metadata_tile_5flayer_2eproto[1]);
}

// ===================================================================

class tile_layer::_Internal {
 public:
  using HasBits = decltype(std::declval<tile_layer>()._has_bits_);
  static const ::wanderer::proto::tile_matrix& matrix(const tile_layer* msg);
  static void set_has_matrix(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
  static void set_has_z_index(HasBits* has_bits) {
    (*has_bits)[0] |= 2u;
  }
};

const ::wanderer::proto::tile_matrix&
tile_layer::_Internal::matrix(const tile_layer* msg) {
  return *msg->matrix_;
}
tile_layer::tile_layer(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:wanderer.proto.tile_layer)
}
tile_layer::tile_layer(const tile_layer& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  if (from._internal_has_matrix()) {
    matrix_ = new ::wanderer::proto::tile_matrix(*from.matrix_);
  } else {
    matrix_ = nullptr;
  }
  z_index_ = from.z_index_;
  // @@protoc_insertion_point(copy_constructor:wanderer.proto.tile_layer)
}

void tile_layer::SharedCtor() {
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&matrix_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&z_index_) -
    reinterpret_cast<char*>(&matrix_)) + sizeof(z_index_));
}

tile_layer::~tile_layer() {
  // @@protoc_insertion_point(destructor:wanderer.proto.tile_layer)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void tile_layer::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  if (this != internal_default_instance()) delete matrix_;
}

void tile_layer::ArenaDtor(void* object) {
  tile_layer* _this = reinterpret_cast< tile_layer* >(object);
  (void)_this;
}
void tile_layer::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void tile_layer::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void tile_layer::Clear() {
// @@protoc_insertion_point(message_clear_start:wanderer.proto.tile_layer)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    GOOGLE_DCHECK(matrix_ != nullptr);
    matrix_->Clear();
  }
  z_index_ = 0;
  _has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* tile_layer::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // optional .wanderer.proto.tile_matrix matrix = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          ptr = ctx->ParseMessage(_internal_mutable_matrix(), ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // optional int32 z_index = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          _Internal::set_has_z_index(&has_bits);
          z_index_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
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

::PROTOBUF_NAMESPACE_ID::uint8* tile_layer::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:wanderer.proto.tile_layer)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // optional .wanderer.proto.tile_matrix matrix = 1;
  if (_internal_has_matrix()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        1, _Internal::matrix(this), target, stream);
  }

  // optional int32 z_index = 2;
  if (_internal_has_z_index()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(2, this->_internal_z_index(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:wanderer.proto.tile_layer)
  return target;
}

size_t tile_layer::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:wanderer.proto.tile_layer)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    // optional .wanderer.proto.tile_matrix matrix = 1;
    if (cached_has_bits & 0x00000001u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
          *matrix_);
    }

    // optional int32 z_index = 2;
    if (cached_has_bits & 0x00000002u) {
      total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32SizePlusOne(this->_internal_z_index());
    }

  }
  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData tile_layer::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    tile_layer::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*tile_layer::GetClassData() const { return &_class_data_; }

void tile_layer::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<tile_layer *>(to)->MergeFrom(
      static_cast<const tile_layer &>(from));
}


void tile_layer::MergeFrom(const tile_layer& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:wanderer.proto.tile_layer)
  GOOGLE_DCHECK_NE(&from, this);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    if (cached_has_bits & 0x00000001u) {
      _internal_mutable_matrix()->::wanderer::proto::tile_matrix::MergeFrom(from._internal_matrix());
    }
    if (cached_has_bits & 0x00000002u) {
      z_index_ = from.z_index_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void tile_layer::CopyFrom(const tile_layer& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:wanderer.proto.tile_layer)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool tile_layer::IsInitialized() const {
  return true;
}

void tile_layer::InternalSwap(tile_layer* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(tile_layer, z_index_)
      + sizeof(tile_layer::z_index_)
      - PROTOBUF_FIELD_OFFSET(tile_layer, matrix_)>(
          reinterpret_cast<char*>(&matrix_),
          reinterpret_cast<char*>(&other->matrix_));
}

::PROTOBUF_NAMESPACE_ID::Metadata tile_layer::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_tile_5flayer_2eproto_getter, &descriptor_table_tile_5flayer_2eproto_once,
      file_level_metadata_tile_5flayer_2eproto[2]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace proto
}  // namespace wanderer
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::wanderer::proto::tile_row* Arena::CreateMaybeMessage< ::wanderer::proto::tile_row >(Arena* arena) {
  return Arena::CreateMessageInternal< ::wanderer::proto::tile_row >(arena);
}
template<> PROTOBUF_NOINLINE ::wanderer::proto::tile_matrix* Arena::CreateMaybeMessage< ::wanderer::proto::tile_matrix >(Arena* arena) {
  return Arena::CreateMessageInternal< ::wanderer::proto::tile_matrix >(arena);
}
template<> PROTOBUF_NOINLINE ::wanderer::proto::tile_layer* Arena::CreateMaybeMessage< ::wanderer::proto::tile_layer >(Arena* arena) {
  return Arena::CreateMessageInternal< ::wanderer::proto::tile_layer >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>