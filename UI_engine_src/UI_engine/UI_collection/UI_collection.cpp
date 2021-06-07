#include "UI_collection.h"

UI_collection::UI_collection(
	float x,
	float y,
	float t
) 
{
	init();

	Collection_itemOrder = new UI_vectorRenderList();
	Collection_items = new UI_mapRenderList();

	interface->x = x;
	interface->y = y;
	transparency(t);
};
UI_collection::~UI_collection() {};

void UI_collection::increaseWidth(float percent) {
	for (auto& ui : *Collection_itemOrder) {
		ui->width((ui->width()/100.0f)*percent), ui->x((ui->x() / 100.0f) * percent);
	}
};

void UI_collection::increaseHeight(float percent) {
	for (auto& ui : *Collection_itemOrder) {
		ui->height((ui->height() / 100.0f) * percent), ui->y((ui->y() / 100.0f) * percent);
	}
};

UI* UI_collection::object(std::string name) {
	return (*Collection_items)[name];
};

UI* UI_collection::object(int number) {
	return (*Collection_itemOrder)[number];
};

int UI_collection::objects() {
	return (*Collection_itemOrder).size();
};