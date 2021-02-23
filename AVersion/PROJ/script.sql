CREATE TABLE MISSION (
	Name VARCHAR(100) PRIMARY KEY
);

CREATE TABLE TRAINER (
	ID INTEGER PRIMARY KEY,
	Name VARCHAR(100),
	PokeDollar INTEGER,
	Pokeball INTEGER,
	Potion INTEGER,
	Revive INTEGER
);

CREATE TABLE PARTICIPATE (
	Status INTEGER,
	IDTrainer INTEGER,
	NameMission VARCHAR(100),
	FOREIGN KEY (IDTrainer) REFERENCES TRAINER (ID),
	FOREIGN KEY (NameMission) REFERENCES MISSION (Name),
	PRIMARY KEY (IDTrainer, NameMission)
);

CREATE TABLE POKEMON (
	Name VARCHAR(50) PRIMARY KEY,
	PV INTEGER,
	Attack INTEGER,
	Defense INTEGER,
	Speed INTEGER
);

CREATE TABLE POKEBALL (
	NamePerso VARCHAR(32),
	ID INTEGER PRIMARY KEY,
	LVL INTEGER,
	XP INTEGER,
	IDTrainer INTEGER NOT NULL,
	NamePokemon VARCHAR(50) NOT NULL,
	PC INTEGER,
	FOREIGN KEY (IDTrainer) REFERENCES TRAINER (ID),
	FOREIGN KEY (NamePokemon) REFERENCES POKEMON (Name)
);

CREATE TABLE LOCATION (
	Name VARCHAR(100) PRIMARY KEY
);

CREATE TABLE LIVES (
	NamePokemon VARCHAR(50),
	NameLocation VARCHAR(100),
	FOREIGN KEY (NamePokemon) REFERENCES POKEMON (Name),
	FOREIGN KEY (NameLocation) REFERENCES LOCATION (Name),
	PRIMARY KEY (NamePokemon, NameLocation)
);

CREATE TABLE TYPE (
	Name VARCHAR(100) PRIMARY KEY
);

CREATE TABLE AMPLIFICATOR (
	NameAttack VARCHAR(100) NOT NULL,
	NameDefense VARCHAR(100) NOT NULL,
	Value DOUBLE,
	FOREIGN KEY (NameAttack) REFERENCES TYPE(Name),
	FOREIGN KEY (NameDefense) REFERENCES TYPE(Name),
	PRIMARY KEY (NameAttack, NameDefense)
);

CREATE TABLE BELONGSTO (
	NamePokemon VARCHAR(50),
	NameType VARCHAR(100),
	FOREIGN KEY (NamePokemon) REFERENCES POKEMON(Name),
	FOREIGN KEY (NameType) REFERENCES TYPE(Name),
	PRIMARY KEY (NamePokemon, NameType)
);

CREATE TABLE ATTACK (
	Name VARCHAR(100) PRIMARY KEY,
	Power INTEGER,
	Acc INTEGER,
	NameType VARCHAR(100),
	FOREIGN KEY (NameType) REFERENCES TYPE(Name)
);

CREATE TABLE LEARN (
	NamePokemon VARCHAR(50),
	NameAttack VARCHAR(100),
	LVL INTEGER,
	FOREIGN KEY (NamePokemon) REFERENCES POKEMON(Name),
	FOREIGN KEY (NameAttack) REFERENCES ATTACK(Name),
	PRIMARY KEY (NamePokemon, NameAttack)
);
