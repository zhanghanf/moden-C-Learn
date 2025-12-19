#pragma once
//控制自由存储区heap和bucket的分配和释放
struct Bucket {
	const static size_t SIZE = 4096;
	std::byte data[SIZE];
};
//创建一个1MB的大桶
struct LargeBucket {
	const static size_t SIZE = 1024 * 1024;
	std::byte data[SIZE];
};
//扩展heap类以支持大桶分配
struct Heap {
	void* allocate(size_t size) {
		if (size > Bucket::SIZE) {//请求的大小超过单个Bucket的大小
			for (auto& largeBucket : largeBuckets) {//查找一个未使用的大桶
				if (!bucketInUse[&largeBucket - largeBuckets + MAX_BUCKETS]) {
					bucketInUse[&largeBucket - largeBuckets + MAX_BUCKETS] = true;
					return static_cast<void*>(largeBucket.data);//返回大桶的数据指针
				}
			}
			throw std::bad_alloc();
		}
		for (auto& bucket : buckets) {//查找一个未使用的Bucket
			if (!bucketInUse[&bucket - buckets]) {
				bucketInUse[&bucket - buckets] = true;
				return static_cast<void*>(bucket.data);//返回Bucket的数据指针
			}
		}
		throw std::bad_alloc();
	}
	void free(void* ptr) {//接受一个指针并释放对应的Bucket
		for (auto& bucket : buckets) {
			if (static_cast<void*>(bucket.data) == ptr) {
				bucketInUse[&bucket - buckets] = false;
				return;
			}
		}
		for (auto& largeBucket : largeBuckets) {
			if (static_cast<void*>(largeBucket.data) == ptr) {
				bucketInUse[&largeBucket - largeBuckets + MAX_BUCKETS] = false;
				return;
			}
		}
	}
	static const size_t MAX_BUCKETS = 10;
	Bucket buckets[MAX_BUCKETS]{};//包含MAX_BUCKETS个Bucket对象
	bool bucketInUse[MAX_BUCKETS] = { false };//跟踪每个Bucket是否被使用
	LargeBucket largeBuckets[MAX_BUCKETS];//包含MAX_BUCKETS个LargeBucket对象
	bool largeBucketInUse[MAX_BUCKETS] = { false };//跟踪每个LargeBucket是否被使用
};

// 测试Heap和Bucket
	//通过重载运算符new和delete来使用自定义的Heap分配器
Heap heap;
void* operator new(std::size_t size) {
	return heap.allocate(size);
}
void operator delete(void* ptr) noexcept {
	heap.free(ptr);
}
//布置运算符new和delete的重载