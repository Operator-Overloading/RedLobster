// RENERING/include/Shader.hpp

#pragma once
#include <string>
#include <vector>

namespace Lobster
{
	enum class ShaderDataType : unsigned short
	{
		// Scalars
		Bool = 0xB1,
		Int = 0x1, UInt = 0x10,
		Float = 0xF1, Double = 0xD1,

		// Vectors
		BVec2 = 0xB2, BVec3 = 0xB3, BVec4 = 0xB4,
		IVec2 = 0x2, IVec3 = 0x3, IVec4 = 0x4,
		UVec2 = 0x20, UVec3 = 0x30, UVec4 = 0x40,
		Vec2 = 0xF2, Vec3 = 0xF3, Vec4 = 0xF4,
		DVec2 = 0xD2, DVec3 = 0xD3, DVec4 = 0xD4,

		// Matrices
		Mat2 = 0x22, Mat3 = 0x33, Mat4 = 0x44,
		Mat2x3 = 0x23, Mat2x4 = 0x24, Mat3x2 = 0x32, Mat3x4 = 0x34, Mat4x2 = 0x42, Mat4x3 = 0x43,
		DMat2 = 0xD22, DMat3 = 0xD33, DMat4 = 0xD44,

		// Textures and Samplers
		Sampler1D = 0x1D, Sampler2D = 0x2D, Sampler3D = 0x3D, SamplerCube = 0x0C,
		Sampler1DArray = 0x1DA, Sampler2DArray = 0x2DA, SamplerCubeArray = 0x0CA,
		Sampler2DMS = 0x2DE, Sampler2DMSArray = 0x2DEA,

		// Storage images
		Image1D = 0xC1, Image2D = 0xC2, Image3D = 0xC3, ImageCube = 0xCC,
		Image1DArray = 0xC1A, Image2DArray = 0xC2A, ImageCubeArray = 0xCCA,

		// Atomic counters
		AtomicCounter = 0xAC,

		// Special types
		Struct = 0xCCC, Array = 0xAAA, BufferReference = 0xBBB,
	};

	struct ShaderTypeInfo
	{
		ShaderDataType type;
		std::string name;

		// Size in bytes
		uint32_t size;

		// 1 for scalar, 4 for vec4, 16 for mat4, etc.
		uint32_t componentCount;

		// Underlying base type
		uint32_t baseType;

		bool isScalar;
		bool isVector;
		bool isMatrix;
		bool isTexture;
		bool isSampler;

		// For arrays and structs
		uint32_t arraySize;     // 0 for not array, >0 for fixed size, -1 for dynamic
		std::vector<ShaderTypeInfo> members;
	};

	struct ShaderUniform
	{
		//  The name for the variable that is specified in the shader
		std::string name;

		//  Enum above, Datatype signature
		ShaderDataType type;

		//  Size in bytes
		uint32_t size;

		//  Location of the uniform .. layout(location = ?)
		uint32_t location;

		//  For descriptor sets/bind points
		uint32_t binding;

		//  For Vulkan descriptor sets
		uint32_t set;
	};

	struct ShaderAttribute
	{
		std::string name;

		ShaderDataType type;

		uint32_t location;

		uint32_t size;
	};

	struct ShaderResource
	{
		std::string name;

		ShaderDataType type;

		uint32_t binding;

		uint32_t set;
	};
}