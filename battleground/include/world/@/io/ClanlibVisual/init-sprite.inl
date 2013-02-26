// Инициализация структур визуальных образов элементов портулана.


// ПОЛЕ БИТВЫ
{
    const typelib::json::Variant o = "{"
        " 'alpha': 0.5"
    " }";
    ASSERT( !o.undefined()
        && "Опции не установлены." );
    insert( "battleground  Field",  "library/green-cross-grid-64x64.png",  o );
}





// ВОИН

// простые спрайты

insert( "warrior  Base",    "library/dc/player/base/human_m.2x.png" );
insert( "warrior  Body",    "library/dc/player/body/chainmail3.2x.png" );
insert( "warrior  Legs",    "library/dc/player/legs/leg_armor02.2x.png" );
insert( "warrior  Boots",   "library/dc/player/boots/long_white.2x.png" );
insert( "warrior  Gloves",  "library/dc/player/gloves/glove_white.2x.png" );

insert( "warrior  SwordReady",  "library/dc/player/hand1/boromir.2x.png" );

//insert( "warrior  ActionProgress",    "" );
insert( "warrior  ActionProgress90",  "library/dc/misc/mdam_lightly_damaged.2x.png" );
insert( "warrior  ActionProgress70",  "library/dc/misc/mdam_moderately_damaged.2x.png" );
insert( "warrior  ActionProgress50",  "library/dc/misc/mdam_heavily_damaged.2x.png" );
insert( "warrior  ActionProgress30",  "library/dc/misc/mdam_severely_damaged.2x.png" );
insert( "warrior  ActionProgress10",  "library/dc/misc/mdam_almost_dead.2x.png" );


// составные спрайты

// Воин без меча
{
    const std::vector< keySprite_t >  l = boost::assign::list_of
        ( "warrior  Base" )
        ( "warrior  Body" )
        ( "warrior  Legs" )
        ( "warrior  Boots" )
        ( "warrior  Gloves" )
    ;
    insert( "warrior  WarriorWithoutSword",  l );
}


// спрайты-состояния

// start
{
    // ? меч true
    {
        roughlyStateWarrior_t state = {};
        state.characteristic[ 0 ].sword = true;
        const std::vector< keySprite_t >  l = boost::assign::list_of
            ( "warrior  WarriorWithoutSword" )
            ( "warrior  SwordReady" )
        ;
        const std::string sn =
            "warrior  WarriorWithoutSword + SwordReady";
        insert( state, sn, l );
    }
    // else
    {
        roughlyStateWarrior_t state = {};
        state.characteristic[ 0 ].sword = false;
        const std::vector< keySprite_t >  l = boost::assign::list_of
            ( "warrior  WarriorWithoutSword" )
        ;
        const std::string sn =
            "warrior  WarriorWithoutSword - SwordReady";
        insert( state, sn, l );
    }
}

// continue
{
    // | progress > 0.9
    {
        roughlyStateWarrior_t state = {};
        state.strategy[ 0 ]
        .TrainingSingleSwordTurn.IntoCombatPosition
        .statistics.progress = 0.9;
        state.strategy[ 1 ]
        .TrainingSingleSwordTurn.IntoCombatPosition
        .statistics.progress = 1.0;
        const std::vector< keySprite_t >  l = boost::assign::list_of
            ( "warrior  WarriorWithoutSword" )
            ( "warrior  ActionProgress90" )
        ;
        const std::string sn =
            "warrior  WarriorWithoutSword + ActionProgress90";
        insert( state, sn, l );
    }

    // | progress > 0.8
    {
        roughlyStateWarrior_t state = {};
        state.strategy[ 0 ]
        .TrainingSingleSwordTurn.IntoCombatPosition
        .statistics.progress = 0.8;
        state.strategy[ 1 ]
        .TrainingSingleSwordTurn.IntoCombatPosition
        .statistics.progress = 0.9;
        const std::vector< keySprite_t >  l = boost::assign::list_of
            ( "warrior  WarriorWithoutSword" )
            ( "warrior  ActionProgress70" )
        ;
        const std::string sn =
            "warrior  WarriorWithoutSword + ActionProgress70";
        insert( state, sn, l );
    }

    // ...
}




