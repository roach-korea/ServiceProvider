#pragma once

#include <functional>
#include <memory>
#include <vector>

#define Implements(...) public: using ServiceParent = std::tuple<__VA_ARGS__>; private:
#define Requires(...) public: using ServiceRequirement = ToPtrTuple<__VA_ARGS__>; using ServiceRequirementType = std::tuple<__VA_ARGS__>; private:

class IService {
public:
	virtual ~IService() = default;
};

template <typename T>
using Service = std::shared_ptr<T>;
template <typename... T>
using ToPtrTuple = std::tuple<std::shared_ptr<T>...>;
using ServicePtr = Service<IService>;
template <typename T>
using ServiceList = std::vector<Service<T>>;
using ServicePtrList = std::vector<ServicePtr>;
