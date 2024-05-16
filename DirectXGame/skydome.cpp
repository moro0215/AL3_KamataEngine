#include "skydome.h"
#include <cassert>

Skydome::Skydome(){};

Skydome::~Skydome(){};

void Skydome::Initialize(Model* model, ViewProjection* viewProjection) {
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
	warldTransform_.Initialize();
};

void Skydome::Update(){};

void Skydome::Draw() {

	model_->Draw(warldTransform_, *viewProjection_);
};