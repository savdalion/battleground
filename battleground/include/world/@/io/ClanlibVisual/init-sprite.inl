// Инициализация структур визуальных образов элементов портулана.


// ВОИН

// простые спрайты

insert( "warrior  Base",    "library/dc/player/base/human_f.png" );
insert( "warrior  Body",    "library/dc/player/body/chainmail3.png" );
insert( "warrior  Legs",    "library/dc/player/legs/leg_armor02.png" );
insert( "warrior  Boots",   "library/dc/player/boots/long_white.png" );
insert( "warrior  Gloves",  "library/dc/player/gloves/glove_white.png" );

insert( "warrior  SwordReady",  "library/dc/player/hand1/boromir.png" );

//insert( "warrior  ActionProgress",    "" );
insert( "warrior  ActionProgress90",  "library/dc/misc/mdam_lightly_damaged.png" );
insert( "warrior  ActionProgress70",  "library/dc/misc/mdam_moderately_damaged.png" );
insert( "warrior  ActionProgress50",  "library/dc/misc/mdam_heavily_damaged.png" );
insert( "warrior  ActionProgress30",  "library/dc/misc/mdam_severely_damaged.png" );
insert( "warrior  ActionProgress10",  "library/dc/misc/mdam_almost_dead.png" );


// составные спрайты

// Воин без меча
{
    const std::vector< std::string >  v = boost::assign::list_of
        ( "warrior  Base" )
        ( "warrior  Body" )
        ( "warrior  Legs" )
        ( "warrior  Boots" )
        ( "warrior  Gloves" )
    ;
    insert( "warrior  WarriorWithoutSword",  v );
}


// спрайты-состояния

// start
{
    // ? меч true
    {
        roughlyStateWarrior_t state = {};
        state.characteristic[ 0 ].sword = true;
        const std::vector< std::string >  l = boost::assign::list_of
            ( "warrior  WarriorWithoutSword" )
            ( "warrior  SwordReady" )
        ;
        // @todo fine Свернуть в 1 метод.
        const std::string sn =
            "warrior  WarriorWithoutSword + SwordReady";
        insert( sn, l );
        insert( state, sn );
    }
    // else
    {
        roughlyStateWarrior_t state = {};
        state.characteristic[ 0 ].sword = false;
        const std::string sn =
            "warrior  WarriorWithoutSword + SwordReady";
        insert( state, sn );
    }
}

// continue
{
    // | progress > 0.9
    {
        roughlyStateWarrior_t state = {};
        state.strategy[ 0 ]
        .Training.SingleSword.Turn.IntoCombatPosition
        .statistics.progress = 0.9;
        state.strategy[ 1 ]
        .Training.SingleSword.Turn.IntoCombatPosition
        .statistics.progress = 1.0;
        const std::vector< std::string >  l = boost::assign::list_of
            ( "warrior  WarriorWithoutSword" )
            ( "warrior  ActionProgress90" )
        ;
        // @todo fine Свернуть в 1 метод.
        const std::string sn =
            "warrior  WarriorWithoutSword + ActionProgress90";
        insert( sn, l );
        insert( state, sn );
    }

    // | progress > 0.8
    {
        roughlyStateWarrior_t state = {};
        state.strategy[ 0 ]
        .Training.SingleSword.Turn.IntoCombatPosition
        .statistics.progress = 0.8;
        state.strategy[ 1 ]
        .Training.SingleSword.Turn.IntoCombatPosition
        .statistics.progress = 0.9;
        const std::vector< std::string >  l = boost::assign::list_of
            ( "warrior  WarriorWithoutSword" )
            ( "warrior  ActionProgress80" )
        ;
        const std::string sn =
            "warrior  WarriorWithoutSword + ActionProgress80";
        insert( sn, l );
        insert( state, sn );
    }

    // ...
}
