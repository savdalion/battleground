// Для обмена данными с OpenCL.

std::unique_ptr< characteristicWarrior_t >  characteristicWarriorContentPtr;
std::unique_ptr< actionWarrior_t >  actionWarriorContentPtr;

std::unique_ptr< characteristicBattleground_t >  characteristicBattlegroundContentPtr;
std::unique_ptr< actionBattleground_t >  actionBattlegroundContentPtr;


cl::Buffer characteristicWarriorBCL;
cl::Buffer actionWarriorBCL;

cl::Buffer characteristicBattlegroundBCL;
cl::Buffer actionBattlegroundBCL;
