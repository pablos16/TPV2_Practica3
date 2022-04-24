// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <array>
#include <bitset>
#include <cassert>
#include <vector>

#include "Component.h"
#include "ecs.h"

namespace ecs {

/*
 * A class that represents a collection of components. In principle,
 * we could remove methods update/render since they won't be really
 * called when using Systems (also the field currCmps_). Nevertheless,
 * we leave them just to be able to use this code without systems as
 * well.
 *
 * Managing components is not done any more in the class, we move to the
 * manager (just thinking in the next step where we'll have automatic
 * memory management)
 *
 */
class Entity {
public:
	Entity(ecs::grpId_type gId) :
			currCmps_(),
			cmps_(), //
			alive_(),  //
			gId_(gId) //
	{
		// We reserve the a space for the maximum number of
		// components. This way we avoid resizing the vector.
		//
		currCmps_.reserve(ecs::maxComponentId);
	}

	// we delete the copy constructor/assignment because it is
	// not clear how to copy the components
	//
	Entity(const Entity&) = delete;
	Entity& operator=(const Entity&) = delete;

	// Exercise: define move constructor/assignment for class Entity

	// Destroys the entity
	//
	virtual ~Entity() {

		// we delete all available components
		//
		for (auto c : cmps_)
			if (c != nullptr)
				delete c;
	}

	// Updating  an entity simply calls the update of all
	// components
	//
	void update() {
		auto n = currCmps_.size();
		for (auto i = 0u; i < n; i++)
			currCmps_[i]->update();
	}

	// Rendering an entity simply calls the render of all
	// components
	//
	void render() {
		auto n = currCmps_.size();
		for (auto i = 0u; i < n; i++)
			currCmps_[i]->render();
	}

private:
	friend Manager;

	// the list of components is not really needed when using systems,
	// but for now we keep it just in case
	//
	std::vector<Component*> currCmps_;
	std::array<Component*, maxComponentId> cmps_;
	bool alive_;
	ecs::grpId_type gId_;
};

} // end of name space
