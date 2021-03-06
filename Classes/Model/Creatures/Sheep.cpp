#include "Sheep.h"
#include "..\Values\ModelValues.h"

// 绵羊对象的编号计数器
int Sheep::sheepIdCounter = 0;

// 构造函数
Sheep::Sheep()
	: Animal(++sheepIdCounter, CreatureSpecies::Sheep, CreatureType::Consumer,
	ModelValues::getInstance()->getBasicMass(CreatureSpecies::Sheep),
	ModelValues::getInstance()->getEnergyConversionRatio(CreatureSpecies::Sheep),
	ModelValues::getInstance()->getBasicHealth(CreatureSpecies::Sheep),
	ModelValues::getInstance()->getRangeOfActivity(CreatureSpecies::Sheep),
	ModelValues::getInstance()->getPreyedSpeciesList(CreatureSpecies::Sheep),
	ModelValues::getInstance()->getBirthCoolDown(CreatureSpecies::Sheep)),
	healthReducedByFoodShortage(ModelValues::getInstance()->getBasicHealthReducedByFoodShortage(CreatureSpecies::Sheep))
{

}

// 拷贝构造函数
Sheep::Sheep(const Sheep& sheep) : Animal(++sheepIdCounter, sheep.getSpecies(), sheep.getType(), sheep.getMass(),
	sheep.getEnergyConversionRatio(), sheep.getHealth(), sheep.getRangeOfActivity(), sheep.getPreyedSpeciesList(),
	sheep.getBirthCoolDown()), healthReducedByFoodShortage(sheep.getHealthReducedByFoodShortage())
{

}

// 创建绵羊对象（使用默认纹理）
class Sheep* Sheep::create()
{
	Sheep *sheep = new (std::nothrow) Sheep();
	if (sheep && sheep->initWithFile(ModelValues::getInstance()->getTextureFilePath(CreatureSpecies::Sheep)))
	{
		sheep->autorelease();
		return sheep;
	}
	CC_SAFE_DELETE(sheep);
	return nullptr;
}

// 创建绵羊对象（使用自定义纹理）
class Sheep* Sheep::create(const std::string& filename)
{
	Sheep *sheep = new (std::nothrow) Sheep();
	if (sheep && sheep->initWithFile(filename))
	{
		sheep->autorelease();
		return sheep;
	}
	CC_SAFE_DELETE(sheep);
	return nullptr;
}

// 获取因食物缺少而减少的生命值
const int Sheep::getHealthReducedByFoodShortage() const
{
	return healthReducedByFoodShortage;
}

//食物短缺的影响
void Sheep::influenceOfFoodShortage()
{
	healthReducedByFoodShortage = (1.0f - intake / ModelValues::getInstance()->getAppetite(CreatureSpecies::Sheep))
		* ModelValues::getInstance()->getBasicHealthReducedByFoodShortage(CreatureSpecies::Sheep);
}
