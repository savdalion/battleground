// Топология портулана для класса Topology.
// @see struct.hcl


std::unique_ptr< characteristicWarrior_t >  characteristicWarriorContentPtr;
std::unique_ptr< actionWarrior_t >  actionWarriorContentPtr;

std::unique_ptr< characteristicBattleground_t >  characteristicBattlegroundContentPtr;
std::unique_ptr< actionBattleground_t >  actionBattlegroundContentPtr;




// образы элементов портулана, связанные с состояниями элемента
typedef std::map<
    roughlyStateWarrior_t,
    std::unique_ptr< ClanlibVisualImage >
> visualImageContent_t;
visualImageContent_t  visualImageWarriorContent;
visualImageContent_t  visualImageBattlegroundContent;
