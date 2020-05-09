#pragma once

static std::array<Item*, 62> items =
{
	new Item(" "),
	new Item("reeds"),				//1
	new Item("stone"),				//2
	new Item("ash",true),			//3
	new Item("snow",true),			//4
	new Edible("wild grain",5,true),//5
	new Item("lava chunk"),			//6
	new Item("clay",true),			//7
	new Item("silver ore",true),	//8
	new Item("gold ore",true),		//9
	new Item("obsidion",true),		//10
	new Item("vine"),				//11
	new Edible("mushroom",5),		//12
	new Item("moss",true),			//13
	new Edible("watermelon",12),	//14
	new Edible("fish",15),			//15
	new Item("ice",true),			//16
	new Item("evercold stone"),		//17
	new Item("samara seed"),		//18
	new Edible("dandilion",2),		//19
	new Item("hollow stone"),		//20
	new Item("lillypad"),			//21
	new Item("leaf"),				//22
	new Item("four leaf clover"),	//23
	new Item("basalt",true),		//24
	new Item("blue fire",true),		//25
	new Item("shiny sand",true),	//26
	new Item("smooth sand",true),	//27
	new Item("acidic sand",true),	//28
	new Item("paper",true),			//29
	new Item("rodlike stone"),		//30
	new Item("ink",true),			//31
	new Item("pen"),				//32
	new Item("map"),				//33
	new Item("flour",true),			//34
	new Edible("bread",15,true),	//35
	new Edible("berry",6),			//36
	new Edible("hearty tart",25),	//37
	new Item("brick"),				//38
	new Item("foundry clay",true),	//39
	new Item("silver",true),		//40
	new Item("gold",true),			//41
	new Item("electrum",true),		//42
	new Item("chisel"),				//43
	new Item("foundry brick"),		//44
	new Item("murky essence"),		//45
	new Item("ashy essence"),		//46
	new Item("water essence"),		//47
	new Item("snowy essence"),		//48
	new Item("windy essence"),		//49
	new Item("leafy essence"),		//50
	new Item("fire essence"),		//51
	new Item("sandy essence"),		//52
	new Item("scortched essence"),	//53
	new Item("warm essence"),		//54
	new Item("life essence"),		//55
	new Item("cool essence"),		//56
	new Item("dark essence"),		//57
	new Item("magic essence"),		//58
	new Item("enchanted chisel"),	//59
	new Item("key mold"),			//60
	new Item("monument key")		//61
};
static std::array<Recipe, 32> book =
{
	Recipe(1,29),												//0
	Recipe(2,30),												//1
	Recipe(std::vector<int>({3,4}),31),							//2
	Recipe(std::vector<int>({30,31}),32),						//3
	Recipe(std::vector<int>({29,32}),33),						//4
	Recipe(std::vector<int>({2,5,5}),std::vector<int>({34,2})),	//5
	Recipe(std::vector<int>({34,34}),35),						//6
	Recipe(std::vector<int>({35,36,36,36}),37),					//7
	Recipe(std::vector<int>({6,7}),38),							//8
	Recipe(std::vector<int>({3,7}),39),							//9
	Recipe(std::vector<int>({6,39}),44),						//10
	Recipe(std::vector<int>({6,8}),40),							//11
	Recipe(std::vector<int>({6,9}),41),							//12
	Recipe(std::vector<int>({40,41,41}),42),					//13
	Recipe(42,43),												//14
	Recipe(std::vector<int>({3,3,10}),46),						//15
	Recipe(std::vector<int>({11,12,13}),45),					//16
	Recipe(std::vector<int>({14,15,21}),47),					//17
	Recipe(std::vector<int>({4,16,17}),48),						//18
	Recipe(std::vector<int>({18,19,20}),49),					//19
	Recipe(std::vector<int>({21,22,23}),50),					//20
	Recipe(std::vector<int>({6,24,25}),51),						//21
	Recipe(std::vector<int>({26,27,28}),52),					//22
	Recipe(std::vector<int>({3,6,10}),53),						//23
	Recipe(std::vector<int>({45,46}),57),						//24
	Recipe(std::vector<int>({47,48}),56),						//25
	Recipe(std::vector<int>({49,50}),55),						//26
	Recipe(std::vector<int>({51,52,53}),54),					//27
	Recipe(std::vector<int>({54,55,56,57}),58),					//28
	Recipe(std::vector<int>({43,58}),59),						//29
	Recipe(std::vector<int>({44,59}),60),						//30
	Recipe(std::vector<int>({42,42,42,60}),61),					//31
};

bool Make(std::array<int, 32>& inventory, std::string itemName);