#pragma once
namespace kdt
{
	int Test()
	{
		return 5;
	}

	template<class _Ty>
	class _Vector_iterator
	{
	public:
		_Vector_iterator() = default;

	private:
		_Ty* Pointer = nullptr;
	};

	//template<typename T>
	template<class _Ty>
	class vector
	{
	public:
		using iterator = _Vector_iterator<_Ty>;

		_CONSTEXPR20 void push_back(const _Ty& _Val)
		{
			if (IsFull())
			{
				// 1.5배로 늘리고 싶은 경우
				//size_t NewSize = round(Size * 1.5); // round 함수는 반올림(반올림 안하면 1 * 1.5 = 1)
				// 또는 Size * 1.5 + 0.5
				reserve_impl(Size * 2);
			}

			new(Array + Size)_Ty(_Val);
			++Size;
		}
		_CONSTEXPR20 void push_back(_Ty&& _Val)
		{
			if (IsFull())
			{
				// 1.5배로 늘리고 싶은 경우
				//size_t NewSize = round(Size * 1.5); // round 함수는 반올림(반올림 안하면 1 * 1.5 = 1)
				// 또는 Size * 1.5 + 0.5
				reserve_impl(Size * 2);
			}

			new(Array + Size)_Ty(std::move(_Val));
			++Size;
		}

		_CONSTEXPR20 void reserve(const size_t InSize)
		{
			if (InSize == 0)
			{
				clear();
				return;
			}

			if (Size > InSize)
			{
				return;
			}

			reserve_impl(InSize);
		}

		_CONSTEXPR20 void resize(const size_t InSize)
		{
			if (InSize == 0)
			{
				clear();
				return;
			}

			const size_t OriginSize = Size;
			reserve_impl(InSize);
			for (size_t i = OriginSize; i < InSize; ++i)
			{
				push_back({});
			}
		}

		_CONSTEXPR20 void clear() noexcept
		{
			if (Array == nullptr) { return; }

			for (size_t i = 0; i < Size; ++i)
			{
				Array[i].~_Ty();
			}
			free(Array);
			Array = nullptr;

			Size = 0;
			Capacity = 0;
		}

		_NODISCARD _CONSTEXPR20 bool empty() const noexcept
		{
			return Size == 0;
		}

		_NODISCARD _CONSTEXPR20 size_t size() const noexcept { return Size; }
		_NODISCARD _CONSTEXPR20 size_t capacity() const noexcept { return Capacity; }

		_NODISCARD _CONSTEXPR20 _Ty& operator[](const size_t _Pos) noexcept
		{
			return Array[_Pos];
		}

	public:
		vector() = default;
		~vector()
		{
			if (Capacity != 0)
			{
				clear();
			}
		}

	protected:
		// 내부 호출 전용, InSize가 0인 경우 1로 처리
		// clear 이후 push_back 대응
		void reserve_impl(size_t InSize)
		{
			const static size_t MinSize = 1;
			// end 위치가 될 공간을 위해 + 1 을 해줬다
			const size_t NewCapacity = std::max(InSize, MinSize);
			const size_t NewAllocSize = sizeof(_Ty) * (NewCapacity + 1);
			_Ty* NewArray = reinterpret_cast<_Ty*>(malloc(NewAllocSize));

			// 배열이 비어 있지 않은 경우
			{
				if (!empty())
				{
					// Array에 있던 데이터를 NewArray로 복사
					const size_t OriginSize = Size;
					// 원래 10
					// 5개로 줄어드는 경우
					// 10 > 5 ? NewCapacity(5) : Size(10);
					// 5 > 10 ? NewCapacity(10) : Size(5)
					Size = Size > NewCapacity ? NewCapacity : Size;
					for (size_t i = 0; i < Size; ++i)
					{
						new(NewArray + i)_Ty(std::move(Array[i]));
					}
					for (size_t i = 0; i < OriginSize; ++i)
					{
						Array[i].~_Ty();
					}
				}

				// 복사 이후에 기존 Array는 free
				if (Array)
				{
					free(Array);
					Array = nullptr;
				}
			}

			// 신규 할당된 NewArray의 주소를 Array에 덮어쓴다
			Array = NewArray;
			Capacity = NewCapacity;
		}

	protected:
		bool IsFull() const
		{
			return Size == Capacity;
		}

	protected:
		_Ty* Array = nullptr;
		size_t Size = 0;			// 실제로 할당된 원소의 갯수
		size_t Capacity = 0;		// 할당 가능한 총 원소의 갯수
	};
}