#pragma once

// # Нет пространства имён.
// # Нет включений.


@todo ? Передавать визуальному образу воина указатель на портулан и
      его позицию в портулане. Этот класс - это конкретнный
      (воплощённый) воин.



/**
* ВОИН.
*/
class Warrior :
    public CLIncarnate
{
protected:
    Warrior(
        std::shared_ptr< World >,
        const characteristicWarrior_t&  characteristic,
        const strategyWarrior_t&  strategy
    );




public:
    static std::unique_ptr< Warrior >  valueOf(
        std::shared_ptr< World >,
        const std::string&  name,
        const std::string&  nameTerritory
    );




    virtual ~Warrior();




    void draw();




private:
    /**
    * Загружает ресурсы (в частности, графику).
    */
    void load();




public:
    const characteristicWarrior_t&  characteristic;
    const strategyWarrior_t&  strategy;
};









Warrior::Warrior(
    std::shared_ptr< World >  world,
    const std::string&        name,
    const std::string&        nameTerritory
) :
    GE( world ),
    CLIncarnate( world ),
    mName( name ),
    mNameTerritory( nameTerritory ),
    mConfigure( typelib::json::load(
        "configure.json",
        TERRITORY_PATH_MEDIA + "/" + nameTerritory + "/background/" + name
    ) )
{
#ifdef _DEBUG
    std::cout << "\n\nСобираем фон '" << mName << "'\n";
#endif

    assert( !mName.empty() && "Не указано название фона." );
    assert( !mNameTerritory.empty() && "Не указано название территории для фона." );
    assert( !mConfigure.undefined() && "Конфигурация для фона не найдена." );

    load();

#ifdef _DEBUG
    std::cout << "Фон '" << mName << "' собран.\n\n";
#endif
}




Warrior::~Warrior() {
}




std::unique_ptr< Background >  Warrior::valueOf(
    std::shared_ptr< World >  world,
    const std::string&        name,
    const std::string&        nameTerritory
) {
    return std::unique_ptr< Background >( new Background(
        world, name, nameTerritory
    ) );
}




void Warrior::load() {
    assert( !mConfigure->empty()
        && "Конфигурация для фона не определена." );

    // загружаем спрайты фона
    const std::string BM =
        TERRITORY_PATH_MEDIA + "/" + mNameTerritory + "/background/" + mName;
    addSprite( BM, ".jpg" );
}




void Warrior::draw() {
    // @todo ...
}








