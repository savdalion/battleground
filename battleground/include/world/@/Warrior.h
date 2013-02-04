#pragma once

// # ��� ������������ ���.
// # ��� ���������.


@todo ? ���������� ����������� ������ ����� ��������� �� �������� �
      ��� ������� � ���������. ���� ����� - ��� �����������
      (�����������) ����.



/**
* ����.
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
    * ��������� ������� (� ���������, �������).
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
    std::cout << "\n\n�������� ��� '" << mName << "'\n";
#endif

    assert( !mName.empty() && "�� ������� �������� ����." );
    assert( !mNameTerritory.empty() && "�� ������� �������� ���������� ��� ����." );
    assert( !mConfigure.undefined() && "������������ ��� ���� �� �������." );

    load();

#ifdef _DEBUG
    std::cout << "��� '" << mName << "' ������.\n\n";
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
        && "������������ ��� ���� �� ����������." );

    // ��������� ������� ����
    const std::string BM =
        TERRITORY_PATH_MEDIA + "/" + mNameTerritory + "/background/" + mName;
    addSprite( BM, ".jpg" );
}




void Warrior::draw() {
    // @todo ...
}








