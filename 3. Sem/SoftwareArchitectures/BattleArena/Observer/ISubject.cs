namespace BattleArena
{
    //Subject Interface
    public interface ISubject
    {
        void Subscribe(IObserver observer);
        void Alert();
    }
}
