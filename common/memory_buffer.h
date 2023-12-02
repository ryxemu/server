#ifndef COMMON_MEMORY_BUFFER
#define COMMON_MEMORY_BUFFER

#include "types.h"

#include <type_traits>
#include <string.h>
#include <string>
#include <sstream>

namespace EQ {
class MemoryBuffer {
   public:
	MemoryBuffer();
	MemoryBuffer(size_t sz);
	MemoryBuffer(const MemoryBuffer &other);
	MemoryBuffer(MemoryBuffer &&other);
	MemoryBuffer &operator=(const MemoryBuffer &other);
	MemoryBuffer &operator=(MemoryBuffer &&other);
	MemoryBuffer &operator+=(const MemoryBuffer &rhs);
	friend MemoryBuffer operator+(MemoryBuffer lhs, const MemoryBuffer &rhs) { return lhs += rhs; }
	~MemoryBuffer();

	uchar &operator[](size_t pos);
	const uchar &operator[](size_t pos) const;

	template <typename T>
	operator T *() {
		return reinterpret_cast<T *>(buffer_);
	}

	template <typename T>
	operator T *() const {
		return reinterpret_cast<T *>(buffer_);
	}

	operator bool() { return buffer_ != nullptr; }
	operator bool() const { return buffer_ != nullptr; }

	bool Empty();
	bool Empty() const;
	size_t Size();
	size_t Size() const;
	size_t Capacity();
	size_t Capacity() const;

	void Resize(size_t sz);
	void Clear();
	void Zero();

	template <typename T>
	void Write(T val) {
		static_assert(std::is_pod<T>::value, "MemoryBuffer::Write<T>(T val) only works on pod and string types.");
		Write((const char *)&val, sizeof(T));
	}

	template <typename T>
	T Read() {
		static_assert(std::is_pod<T>::value, "MemoryBuffer::Read<T>() only works on pod and string types.");
		T temp;
		Read((uchar *)&temp, sizeof(T));
		return temp;
	}

	void Write(const std::string &val) {
		Write(val.c_str(), val.length());
		Write((uint8)0);
	}

	void Write(const char *val) {
		size_t len = strlen(val);
		Write(val, len);
		Write((uint8)0);
	}

	std::string ReadString() {
		std::string ret;
		size_t len = strlen((const char *)&buffer_[read_pos_]);
		ret.resize(len);
		memcpy(&ret[0], &buffer_[read_pos_], len);
		read_pos_ += len + 1;
		return ret;
	}

	void Write(const char *val, size_t len);
	void Read(uchar *buf, size_t len);
	void Read(char *str);

	inline size_t GetWritePosition() { return write_pos_; }
	inline void SetWritePosition(size_t wp) { write_pos_ = wp; }
	inline void WriteSkipBytes(size_t skip) { write_pos_ += skip; }
	inline size_t GetReadPosition() { return read_pos_; }
	inline void SetReadPosition(size_t rp) { read_pos_ = rp; }
	inline void ReadSkipBytes(size_t skip) { read_pos_ += skip; }

   private:
	uchar *buffer_;
	size_t size_;
	size_t capacity_;
	size_t write_pos_;
	size_t read_pos_;
};

class OutBuffer : public std::stringstream {
   public:
	inline size_t size() { return static_cast<size_t>(tellp()); }
	void overwrite(OutBuffer::pos_type position, const char *_Str, std::streamsize _Count);
	uchar *detach();
};

}  // namespace EQ

#endif /*COMMON_MEMORY_BUFFER*/
