//CharacterBuilder.cpp
//Logic-only Character-Builder for RPG world
//Author: Kaden
//Descritpion: Portfolio project demonstrating gameplay systems logic
//version: 1.00

#include <iostream>
#include <vector>
#include <string>
#include <limits>

enum class ERace {ERHuman, ERElf, EROrc, ERDwarf, ERGnome, ERTiefling};

enum class EClass{ECFighter, ECMonk, ECPaladin, ECWizard, ECCleric, ECSorcerer, ECBard, ECDruid};

struct FAttributes
{
	int Strength = 0;
	int Dexterity = 0;
	int Constitution = 0;
	int Intelligence = 0;
	int Wisdom = 0;
	int Charisma = 0;
};

struct FRaceData
{
	ERace Race;
	FAttributes AttributeModifiers;
};

struct FClassData
{
	EClass Class;
	FAttributes BaseAttributes;
};

struct FCharacter
{
	std::string Name;
	ERace Race;
	EClass Class;
	FAttributes CharacterAttributes;
};

class FCharacterCreator
{
public:
	FCharacterCreator();
	void CreateCharacter();

private:
	void ChooseRace();
	void ChooseClass();
	void AllocateAttributes();
	void ApplyRaceModifiers();
	void ApplyClassBaseStats();
	void PrintCharacter() const;

	std::string ERaceToString(ERace Race) const;
	std::string EClassToString(EClass Class) const;

private:
	FCharacter CurrentCharacter;
	
	std::vector<FRaceData> AvailableRaces;
	std::vector<FClassData> AvailableClasses;

	int AvailableAttributePoints = 10;
};

FCharacterCreator::FCharacterCreator()
{
	AvailableRaces = 
	{
		{ERace::ERHuman, FAttributes{1, 1, 1, 1, 1, 1}},
		{ERace::ERElf, FAttributes{0, 1, 0, 0, 2, 0}},
		{ERace::EROrc, FAttributes{2, 0, 1, 0, 0, 0}},
		{ERace::ERDwarf, FAttributes{1, 0, 2, 0, 0, 0}},
		{ERace::ERGnome, FAttributes{0, 1, 0, 2, 0, 0}},
		{ERace::ERTiefling, FAttributes{0, 1, 0, 0, 0, 2}}
	};

	AvailableClasses = 
	{
		{EClass::ECFighter, FAttributes{2, 0, 1, 0, 0, 0}}, 
		{EClass::ECMonk, FAttributes{0, 2, 0, 0, 1, 0}}, 
		{EClass::ECPaladin, FAttributes{1, 0, 0, 0, 0, 2}}, 
		{EClass::ECWizard, FAttributes{0, 0, 1, 2, 0, 0}}, 
		{EClass::ECCleric, FAttributes{1, 0, 0, 0, 2, 0}}, 
		{EClass::ECSorcerer, FAttributes{0, 0, 1, 0, 0, 2}}, 
		{EClass::ECBard, FAttributes{0, 1, 0, 0, 0, 2}}, 
		{EClass::ECDruid, FAttributes{0, 1, 0, 0, 2, 0}}
	};
}

void FCharacterCreator::CreateCharacter()
{
	std::cout << "Any good adventurer has a good name, choose one for your character: ";
	std::cin >> CurrentCharacter.Name;
	
	ChooseClass();
	ChooseRace();

	ApplyClassBaseStats();
	ApplyRaceModifiers();

	//print character to see what the base stats are after class and race are chosen
	PrintCharacter();

	AllocateAttributes();

	//update player if the current class and stat choices
	PrintCharacter();
}

void FCharacterCreator::ChooseRace()
{
	int RaceNumber = 1;
	std::cout << "Please choose among the available races to play: " << std::endl;
	//Display a list of the available races to choose, the UI should allow selecting(this example will use a number option)
	for (const FRaceData& RaceData : AvailableRaces)
	{
		std::cout << RaceNumber << " " << ERaceToString(RaceData.Race) << std::endl;
		//this is to accompany the number choice and should not be in game
		RaceNumber ++;
	}
	
	//This will be gone in game and only used for testing on logic-only
	size_t ChosenRace = 0;
	
	while(true)
	{
		std::cout << "Choose the number of the race you wish to play: \n";
		
		std::cin >> ChosenRace;
		
		if (std::cin.fail() || ChosenRace < 1 || ChosenRace > AvailableRaces.size())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Please enter a valid number between 1 and " << AvailableRaces.size() << std::endl;
		}
		else
		{
			CurrentCharacter.Race = AvailableRaces[ChosenRace - 1].Race;
			std::cout << "You have chosen to play as a: " << ERaceToString(CurrentCharacter.Race) <<std::endl;
			break;
		}

	}	
}

void FCharacterCreator::ChooseClass()
{
	size_t ClassNumber = 1;
	std::cout << "Please choose among the available Classes to play: " << std::endl;
	//Display a list of the available classes to choose, the UI should allow selecting(this example will use a number option)
	for (const FClassData& ClassData : AvailableClasses)
	{
		std::cout << ClassNumber << " " << EClassToString(ClassData.Class) << std::endl;
		//this is to accompany the number choice and should not be in game
		ClassNumber ++;
	}
	
	//This will be gone in game and only used for testing on logic-only
	int ChosenClass = 0;
	
	while(true)
	{
		std::cout << "Choose the number of the class you wish to play: \n";
		
		std::cin >> ChosenClass;
		
		if (std::cin.fail() || ChosenClass < 1 || ChosenClass > AvailableClasses.size())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Please enter a valid number between 1 and " << AvailableClasses.size() << std::endl;
		}
		else
		{
			CurrentCharacter.Class = AvailableClasses[ChosenClass - 1].Class;
			std::cout << "You have chosen to play as a: " << EClassToString(CurrentCharacter.Class) << std::endl;
			break;
		}

	}
}

void FCharacterCreator::AllocateAttributes()
{
	int StatToIncrease = 0;
	
	std::cout << "Input the number of the stat that you wish to increase by 1: " << std::endl
		  << "1 Strength" << std::endl
		  << "2 Dexterity" << std::endl
		  << "3 Constitution" << std::endl
		  << "4 Intelligence" << std::endl
		  << "5 Wisdom" << std::endl
		  << "6 Charisma" << std::endl;

	while (AvailableAttributePoints != 0)
	{
		std::cout << "Attribute Points Left: " << AvailableAttributePoints << std::endl;

		//Number choice used to mimic a counter to modify stats
		std::cin >> StatToIncrease;

		if (std::cin.fail() || StatToIncrease < 1 || StatToIncrease > 6)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Please enter a valid number between 1 and 6!" << std::endl;
		}
		else
		{
			// switch case used to mimic the use of a counter for incresing stats
			switch(StatToIncrease)
			{
				case 1 : 
					CurrentCharacter.CharacterAttributes.Strength++;
					std::cout << "Strength Increase By 1 to " << CurrentCharacter.CharacterAttributes.Strength << std::endl;
					break;
				case 2 : 
					CurrentCharacter.CharacterAttributes.Dexterity++;
					std::cout << "Dexterity Increase By 1 to " << CurrentCharacter.CharacterAttributes.Dexterity << std::endl;
					break;
				case 3 : 
					CurrentCharacter.CharacterAttributes.Constitution++;
					std::cout << "Constitution Increase By 1 to " << CurrentCharacter.CharacterAttributes.Constitution << std::endl;
					break;
				case 4 : 
					CurrentCharacter.CharacterAttributes.Intelligence++;
					std::cout << "Intelligence Increase By 1 to " << CurrentCharacter.CharacterAttributes.Intelligence << std::endl;
					break;
				case 5 : 
					CurrentCharacter.CharacterAttributes.Wisdom++;
					std::cout << "Wisdom Increase By 1 to " << CurrentCharacter.CharacterAttributes.Wisdom << std::endl;
					break;
				case 6 : 
					CurrentCharacter.CharacterAttributes.Charisma++;
					std::cout << "Charisma Increase By 1 to " << CurrentCharacter.CharacterAttributes.Charisma << std::endl;
					break;
				default:
					std::cout << "It seems that stat does not exist" << std::endl;
					
			}
			--AvailableAttributePoints;
		}
				
	}
}

void FCharacterCreator::ApplyRaceModifiers()
{
	//Iterates through the available race to see if the CurrentCharacters race is there and then adjusts the characters stats according to the race attribute modifier
	for (FRaceData& RaceData : AvailableRaces)
	{
		if (CurrentCharacter.Race == RaceData.Race)
		{
			CurrentCharacter.CharacterAttributes.Strength += RaceData.AttributeModifiers.Strength;
			CurrentCharacter.CharacterAttributes.Dexterity += RaceData.AttributeModifiers.Dexterity;
			CurrentCharacter.CharacterAttributes.Constitution += RaceData.AttributeModifiers.Constitution;
			CurrentCharacter.CharacterAttributes.Intelligence += RaceData.AttributeModifiers.Intelligence;
			CurrentCharacter.CharacterAttributes.Wisdom += RaceData.AttributeModifiers.Wisdom;
			CurrentCharacter.CharacterAttributes.Charisma += RaceData.AttributeModifiers.Charisma;
		}
	}	
}

void FCharacterCreator::ApplyClassBaseStats()
{
	//Iterates through the available classes to see if the CurrentCharacters class is there and then adjusts the characters stats according to the class base stats
	for  (FClassData& ClassData : AvailableClasses)
	{
		if (CurrentCharacter.Class == ClassData.Class)
		{
			CurrentCharacter.CharacterAttributes.Strength += ClassData.BaseAttributes.Strength;
			CurrentCharacter.CharacterAttributes.Dexterity += ClassData.BaseAttributes.Dexterity;
			CurrentCharacter.CharacterAttributes.Constitution += ClassData.BaseAttributes.Constitution;
			CurrentCharacter.CharacterAttributes.Intelligence += ClassData.BaseAttributes.Intelligence;
			CurrentCharacter.CharacterAttributes.Wisdom += ClassData.BaseAttributes.Wisdom;
			CurrentCharacter.CharacterAttributes.Charisma += ClassData.BaseAttributes.Charisma;
		}
	}
}

void FCharacterCreator::PrintCharacter() const
{
	std::cout << "Name: " << CurrentCharacter.Name << std::endl 
		  << "Race: " << ERaceToString(CurrentCharacter.Race) << std::endl
		  << "Class: " << EClassToString(CurrentCharacter.Class) << std::endl
		  << "STR: " << CurrentCharacter.CharacterAttributes.Strength << std::endl
		  << "DEX: " << CurrentCharacter.CharacterAttributes.Dexterity << std::endl 
		  << "CON: " << CurrentCharacter.CharacterAttributes.Constitution << std::endl 
		  << "INT: " << CurrentCharacter.CharacterAttributes.Intelligence << std::endl 
		  << "WIS: " << CurrentCharacter.CharacterAttributes.Wisdom << std::endl 
		  << "CHA: " << CurrentCharacter.CharacterAttributes.Charisma << std::endl;
}

std::string FCharacterCreator::ERaceToString(ERace Race) const
{
	switch(Race) 
	{
		case ERace::ERHuman : return "Human";
		case ERace::ERElf : return "Elf"; 
		case ERace::EROrc : return "Orc"; 
		case ERace::ERDwarf : return "Dwarf"; 
		case ERace::ERGnome : return "Gnome"; 
		case ERace::ERTiefling : return "Tiefling";
		default : return "No Race selected";
	}
}

std::string FCharacterCreator::EClassToString(EClass Class) const
{
	switch(Class)
	{
		case EClass::ECFighter : return "Fighter"; 
		case EClass::ECMonk : return "Monk";
		case EClass::ECPaladin : return "Paladin"; 
		case EClass::ECWizard : return "Wizard"; 
		case EClass::ECCleric : return "Cleric"; 
		case EClass::ECSorcerer : return "Sorcerer"; 
		case EClass::ECBard : return "Bard";
		case EClass::ECDruid : return "Druid";
		default : return "No Class selected";
	}
}