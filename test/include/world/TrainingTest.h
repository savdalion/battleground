#pragma once

#include "../include/configure.h"
#include "../../../battleground/battleground.h"


namespace battleground {
    namespace test {

/**
* # Время - измерение, проходящее сквозь все портуланы. Указывается в секундах.
*/
static const real_t SECOND     = 1.0f;
static const real_t MINUTE     = SECOND * 60.0f;
static const real_t HOUR       = MINUTE * 60.0f;
static const real_t DAY        = HOUR   * 24.0f;
static const real_t HALF_DAY   = DAY    / 2.0f;
static const real_t WEEK       = DAY    * 7.0f;
static const real_t MONTH      = DAY    * 30.0f;
static const real_t HALF_MONTH = MONTH  / 2.0f;
static const real_t YEAR       = DAY    * 365.0f;
static const real_t HALF_YEAR  = YEAR   / 2.0f;


/**
* Влияет на точность рассчётов (больше - ниже).
* Может быть задействован вместе с 'PULSE'.
*/
static const real_t TIMESTEP = SECOND;


/*
* # Учитываем инициал. движка поля битвы, а именно - 'timestep'.
* 'PULSE' влияет на кол-во отрисовок (больше пульс - меньше кадров).
* Может быть задействована вместе с 'timestep'.
* Движок честно считает 'PULSE' кадров с шагом 'timestep' и только
* после - показывает картинку. Др. словами, реальное время отображаемых
* кадров = timestep * PULSE.
* @example timestep = HOUR,  PULSE = 365 * 24 - В Солнечной системе Земля будет
*          оставаться почти неподвижной, т.к. её период обращения ~ 365 дней.
* @example timestep = MINUTE,  PULSE = 60 - просчитываться модель будет
*          с точностью до 1 минуты, отображаться - каждый час своей жизни.
*/
static const int PULSE = 60;




/**
* Слушатель для подсчёта кол-ва событий у элемента поля битвы.
*/
#if 0
// - @todo
template< class L >
class CounterEventListener :
    public L
{
public:
    inline CounterEventListener() {
    }


    virtual inline ~CounterEventListener() {
    }




    /**
    * @return Количество событий с заданным 'uid' события.
    */
    inline size_t countByUIDEvent(
        enum pns::EVENT uid
    ) const {
        const auto ftr = storeCountByUIDEvent.find( uid );
        return (ftr == storeCountByUIDEvent.cend()) ? 0 : ftr->second;
    }




    /**
    * @return Количество событий с заданным 'uid' события, в которых первый
    *         участник - с заданным 'uu' в качестве UID элемента.
    */
    inline size_t countByUIDEvent(
        enum pns::EVENT uid,
        pns::uid_t uu
    ) const {
        size_t n = 0;
        for (auto itr = storeAll.cbegin(); itr != storeAll.cend(); ++itr) {
            const pns::pointerElement_t& piA = itr->first;
            const pns::eventTwo_t& e = itr->second;
            if ( (piA.uu == uu) && (e.uid == uid) ) {
                ++n;
            }
        }
        return n;
    }




    /**
    * @return Количество событий с заданным 'uid' события, в которых второй
    *         участник - из группы элементов 'ge'.
    */
    inline size_t countByUIDEvent(
        enum pns::EVENT uid,
        enum pns::GROUP_ELEMENT ge
    ) const {
        size_t n = 0;
        for (auto itr = storeAll.cbegin(); itr != storeAll.cend(); ++itr) {
            const pns::eventTwo_t& e = itr->second;
            const pns::pointerElement_t& piB = e.pi;
            if ( (e.uid == uid) && (piB.ge == ge) ) {
                ++n;
            }
        }
        return n;
    }




    /**
    * @return Количество событий с заданным 'uid' события, в которых второй
    *         участник - из группы элементов 'ge' с заданным 'uu' в
    *         качестве UID элемента.
    */
    inline size_t countByUIDEvent(
        enum pns::EVENT uid,
        enum pns::GROUP_ELEMENT ge,
        pns::uid_t uu
    ) const {
        size_t n = 0;
        for (auto itr = storeAll.cbegin(); itr != storeAll.cend(); ++itr) {
            const pns::eventTwo_t& e = itr->second;
            const pns::pointerElement_t& piB = e.pi;
            if ( (e.uid == uid) && (piB.ge == ge) && (piB.uu == uu) ) {
                ++n;
            }
        }
        return n;
    }




private:
    virtual inline void beforeEvent(
        const pns::pointerElement_t& piA,
        const pns::eventTwo_t& e
    ) {
        // соберём события
        {
            storeAll.push_back( std::make_pair( piA, e ) );
        }
        {
            auto r = storeCountByUIDEvent.insert( std::make_pair( e.uid, 0 ) );
            ++r.first->second;
        }
        {
            auto r = storeCountByGroupElement.insert( std::make_pair( piA.ge, 0 ) );
            ++r.first->second;
        }
        {
            auto r = storeCountByUIDElement.insert( std::make_pair( piA.uu, 0 ) );
            ++r.first->second;
        }
    }




public:
    /**
    * Перечисление всех отловленных событий.
    */
    typedef std::pair< pns::pointerElement_t, pns::eventTwo_t >  all_t;
    std::vector< all_t >  storeAll;

    /**
    * Количество событий по типам события.
    */
    std::map< enum pns::EVENT, size_t >  storeCountByUIDEvent;

    /**
    * Количество событий по группам элементов.
    */
    std::map< enum pns::GROUP_ELEMENT, size_t >  storeCountByGroupElement;

    /**
    * Количество событий по UID элементов.
    */
    std::map< pns::uid_t, size_t >  storeCountByUIDElement;
};
#endif







/**
* Класс-родитель для тестов тренировки элементов портулана "Поле битвы".
*/
class TrainingTest : public ::testing::Test {
/* - @todo
public:
    typedef CounterEventListener< pes::ListenerAsteroid >
        CounterEventListenerAsteroid;
    typedef CounterEventListener< pes::ListenerStar >
        CounterEventListenerStar;
*/

protected:
    inline TrainingTest(
    ) :
        // Инициализируем мир поля битвы
        mWorld( World::valueOf() )
    {
    }




    virtual inline ~TrainingTest() {
    }




    virtual inline void SetUp() = 0;




    virtual void TearDown() {
    };




    inline std::shared_ptr< World >  world() {
        return mWorld;
    }




private:
    std::shared_ptr< World >    mWorld;
};


    } // test
} // battleground









#if 0
// - @todo
namespace std {


template< class L >
inline std::ostream& operator<<(
    std::ostream&  out,
    const CounterEventListener< L >&  cel
) {
    out << "Count all events:  ";
    out << cel.storeAll.size();
    out << std::endl;

    out << "Count events by UIDs of events:  ";
    typelib::printPair( out, cel.storeCountByUIDEvent );
    out << std::endl;

    out << "Count events by groups of elements:  ";
    typelib::printPair( out, cel.storeCountByGroupElement );
    out << std::endl;

    out << "Count events by UIDs of elements:  ";
    typelib::printPair( out, cel.storeCountByUIDElement );
    out << std::endl;

    return out;
}


} // std
#endif
