using BattleArena.Pawn;

namespace BattleArena.Items
{
    public interface IEquipment
    {
        public void Use(Hero other);
    }
}