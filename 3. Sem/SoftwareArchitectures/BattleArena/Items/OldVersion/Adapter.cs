using BattleArena.Items.OldVersion;
using BattleArena.Pawn;

namespace BattleArena.Items
{
    //Adapter - Object Adapter
    //I chose the Object Adapter because I found It much more straightforward to implement and to comprehend.
    //We use it to give 1 of the 2 Heros the LatharSword
    class Adapter : IEquipment
    {
        private readonly LatharSword LatharSword;
        public Adapter(LatharSword mySword)
        {
            LatharSword = mySword;
        }
        public void Use(Hero other)
        {
            other.ReduceHealth(LatharSword.Hit());
        }
    }
}
