// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: tile.proto

#include "tile.pb.h"

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
constexpr Tile::Tile(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : src_(nullptr)
  , texture_index_(uint64_t{0u})
  , id_(0u)
  , depth_index_(0){}
struct TileDefaultTypeInternal {
  constexpr TileDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~TileDefaultTypeInternal() {}
  union {
    Tile _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT TileDefaultTypeInternal _Tile_default_instance_;
}  // namespace proto
}  // namespace wanderer
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_tile_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_tile_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_tile_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_tile_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::Tile, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::Tile, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::Tile, id_),
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::Tile, texture_index_),
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::Tile, src_),
  PROTOBUF_FIELD_OFFSET(::wanderer::proto::Tile, depth_index_),
  2,
  1,
  0,
  3,
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 10, -1, sizeof(::wanderer::proto::Tile)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::wanderer::proto::_Tile_default_instance_),
};

const char descriptor_table_protodef_tile_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\ntile.proto\022\016wanderer.proto\032\nrect.proto"
  "\"\247\001\n\004Tile\022\017\n\002id\030\001 \001(\rH\000\210\001\001\022\032\n\rtexture_in"
  "dex\030\002 \001(\004H\001\210\001\001\022\'\n\003src\030\003 \001(\0132\025.wanderer.p"
  "roto.irectH\002\210\001\001\022\030\n\013depth_index\030\004 \001(\005H\003\210\001"
  "\001B\005\n\003_idB\020\n\016_texture_indexB\006\n\004_srcB\016\n\014_d"
  "epth_indexb\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_tile_2eproto_deps[1] = {
  &::descriptor_table_rect_2eproto,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_tile_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_tile_2eproto = {
  false, false, 218, descriptor_table_protodef_tile_2eproto, "tile.proto", 
  &descriptor_table_tile_2eproto_once, descriptor_table_tile_2eproto_deps, 1, 1,
  schemas, file_default_instances, TableStruct_tile_2eproto::offsets,
  file_level_metadata_tile_2eproto, file_level_enum_descriptors_tile_2eproto, file_level_service_descriptors_tile_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_tile_2eproto_getter() {
  return &descriptor_table_tile_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_tile_2eproto(&descriptor_table_tile_2eproto);
namespace wanderer {
namespace proto {

// ===================================================================

class Tile::_Internal {
 public:
  using HasBits = decltype(std::declval<Tile>()._has_bits_);
  static void set_has_id(HasBits* has_bits) {
    (*has_bits)[0] |= 4u;
  }
  static void set_has_texture_index(HasBits* has_bits) {
    (*has_bits)[0] |= 2u;
  }
  static const ::wanderer::proto::irect& src(const Tile* msg);
  static void set_has_src(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
  static void set_has_depth_index(HasBits* has_bits) {
    (*has_bits)[0] |= 8u;
  }
};

const ::wanderer::proto::irect&
Tile::_Internal::src(const Tile* msg) {
  return *msg->src_;
}
void Tile::clear_src() {
  if (src_ != nullptr) src_->Clear();
  _has_bits_[0] &= ~0x00000001u;
}
Tile::Tile(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:wanderer.proto.Tile)
}
Tile::Tile(const Tile& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  if (from._internal_has_src()) {
    src_ = new ::wanderer::proto::irect(*from.src_);
  } else {
    src_ = nullptr;
  }
  ::memcpy(&texture_index_, &from.texture_index_,
    static_cast<size_t>(reinterpret_cast<char*>(&depth_index_) -
    reinterpret_cast<char*>(&texture_index_)) + sizeof(depth_index_));
  // @@protoc_insertion_point(copy_constructor:wanderer.proto.Tile)
}

void Tile::SharedCtor() {
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&src_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&depth_index_) -
    reinterpret_cast<char*>(&src_)) + sizeof(depth_index_));
}

Tile::~Tile() {
  // @@protoc_insertion_point(destructor:wanderer.proto.Tile)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void Tile::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  if (this != internal_default_instance()) delete src_;
}

void Tile::ArenaDtor(void* object) {
  Tile* _this = reinterpret_cast< Tile* >(object);
  (void)_this;
}
void Tile::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void Tile::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void Tile::Clear() {
// @@protoc_insertion_point(message_clear_start:wanderer.proto.Tile)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    GOOGLE_DCHECK(src_ != nullptr);
    src_->Clear();
  }
  if (cached_has_bits & 0x0000000eu) {
    ::memset(&texture_index_, 0, static_cast<size_t>(
        reinterpret_cast<char*>(&depth_index_) -
        reinterpret_cast<char*>(&texture_index_)) + sizeof(depth_index_));
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Tile::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // optional uint32 id = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          _Internal::set_has_id(&has_bits);
          id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // optional uint64 texture_index = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          _Internal::set_has_texture_index(&has_bits);
          texture_index_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // optional .wanderer.proto.irect src = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 26)) {
          ptr = ctx->ParseMessage(_internal_mutable_src(), ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // optional int32 depth_index = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 32)) {
          _Internal::set_has_depth_index(&has_bits);
          depth_index_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
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

::PROTOBUF_NAMESPACE_ID::uint8* Tile::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:wanderer.proto.Tile)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // optional uint32 id = 1;
  if (_internal_has_id()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(1, this->_internal_id(), target);
  }

  // optional uint64 texture_index = 2;
  if (_internal_has_texture_index()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt64ToArray(2, this->_internal_texture_index(), target);
  }

  // optional .wanderer.proto.irect src = 3;
  if (_internal_has_src()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        3, _Internal::src(this), target, stream);
  }

  // optional int32 depth_index = 4;
  if (_internal_has_depth_index()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(4, this->_internal_depth_index(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:wanderer.proto.Tile)
  return target;
}

size_t Tile::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:wanderer.proto.Tile)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x0000000fu) {
    // optional .wanderer.proto.irect src = 3;
    if (cached_has_bits & 0x00000001u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
          *src_);
    }

    // optional uint64 texture_index = 2;
    if (cached_has_bits & 0x00000002u) {
      total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt64SizePlusOne(this->_internal_texture_index());
    }

    // optional uint32 id = 1;
    if (cached_has_bits & 0x00000004u) {
      total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32SizePlusOne(this->_internal_id());
    }

    // optional int32 depth_index = 4;
    if (cached_has_bits & 0x00000008u) {
      total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32SizePlusOne(this->_internal_depth_index());
    }

  }
  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData Tile::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    Tile::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*Tile::GetClassData() const { return &_class_data_; }

void Tile::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<Tile *>(to)->MergeFrom(
      static_cast<const Tile &>(from));
}


void Tile::MergeFrom(const Tile& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:wanderer.proto.Tile)
  GOOGLE_DCHECK_NE(&from, this);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 0x0000000fu) {
    if (cached_has_bits & 0x00000001u) {
      _internal_mutable_src()->::wanderer::proto::irect::MergeFrom(from._internal_src());
    }
    if (cached_has_bits & 0x00000002u) {
      texture_index_ = from.texture_index_;
    }
    if (cached_has_bits & 0x00000004u) {
      id_ = from.id_;
    }
    if (cached_has_bits & 0x00000008u) {
      depth_index_ = from.depth_index_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void Tile::CopyFrom(const Tile& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:wanderer.proto.Tile)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Tile::IsInitialized() const {
  return true;
}

void Tile::InternalSwap(Tile* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(Tile, depth_index_)
      + sizeof(Tile::depth_index_)
      - PROTOBUF_FIELD_OFFSET(Tile, src_)>(
          reinterpret_cast<char*>(&src_),
          reinterpret_cast<char*>(&other->src_));
}

::PROTOBUF_NAMESPACE_ID::Metadata Tile::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_tile_2eproto_getter, &descriptor_table_tile_2eproto_once,
      file_level_metadata_tile_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace proto
}  // namespace wanderer
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::wanderer::proto::Tile* Arena::CreateMaybeMessage< ::wanderer::proto::Tile >(Arena* arena) {
  return Arena::CreateMessageInternal< ::wanderer::proto::Tile >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
