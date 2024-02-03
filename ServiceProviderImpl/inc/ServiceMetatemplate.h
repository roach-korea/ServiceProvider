#pragma once

template <typename T>
void ConstexprConsume(std::initializer_list<T>) {}

template <typename F, std::size_t... S>
constexpr void ConstexprFor(F&& function, std::index_sequence<S...>) {
	return ConstexprConsume({ (function(std::integral_constant<std::size_t, S> {}), 0)... });
}

template <std::size_t iterations, typename F>
constexpr void ConstexprFor(F&& function) {
	ConstexprFor(std::forward<F>(function), std::make_index_sequence<iterations>());
}

template <typename T>
using EmptyType = void;

template <typename, typename = void>
struct IsRequirementDefined : std::false_type { };

template <typename T>
struct IsRequirementDefined<T, EmptyType<typename T::ServiceRequirement>> : std::true_type { };

template <typename, typename = void>
struct IsParentDefined : std::false_type { };

template <typename T>
struct IsParentDefined<T, EmptyType<typename T::ServiceParent>> : std::true_type { };

template <typename T>
struct IsTuple : std::false_type {};

template <typename... U>
struct IsTuple<std::tuple<U...>> : std::true_type {};

template <class T, class Tuple, std::size_t... I>
constexpr auto NewFromTupleImpl(Tuple&& t, std::index_sequence<I...>) -> T* {
	return new T(std::get<I>(std::forward<Tuple>(t))...);
}

template <class T, class Tuple>
constexpr auto NewFromTuple(Tuple&& t) -> T* {
	return NewFromTupleImpl<T>(std::forward<Tuple>(t), std::make_index_sequence<std::tuple_size_v<std::remove_reference_t<Tuple>>> {});
}

template <class T, class Tuple, std::size_t... I>
constexpr auto IsNewConstructibleImpl(std::index_sequence<I...>) -> bool {
	return std::is_constructible_v<T, std::tuple_element_t<I, Tuple>...>;
}


template <class T, class Tuple>
constexpr auto IsNewConstructible() -> bool {
	return IsNewConstructibleImpl<T, Tuple>(std::make_index_sequence<std::tuple_size_v<std::remove_reference_t<Tuple>>> {});
}

struct SingletonDeleter {
	auto operator()(IService*) const noexcept -> void {}
};

struct ScopedDeleter {
	IService** service;
	int* ref;

	ScopedDeleter(IService*& service, int& ref) : service(&service), ref(&ref) {
		++ref;
	}

	auto operator()(IService*) const noexcept -> void {
		if (--*ref; *ref == 0) {
			delete *service;
			*service = nullptr;
		}
	}
};
