/**
https://csharp-video-tutorials.blogspot.com/2018/01/dependency-inversion-principle.html

The Dependency Inversion Principle introduced by Robert C Martin states that  
High-level modules should not depend on low-level modules. Both should depend on abstractions.
AND
Abstractions should not depend on details. Details should depend on abstractions.

Code without DIP shown below.
*/

public class BusinessLogicLayer
{
    private readonly DataAccessLayer DAL;

    public BusinessLogicLayer()
    {
        DAL = new DataAccessLayer();
    }

    public void Save(Object details)
    {
        DAL.Save(details);
    }
}

public class DataAccessLayer
{
    public void Save(Object details)
    {
        //perform save
    }
}

/**
Notice from the above code the BLL is directly dependent on the low level Data Access Layer and it’s hard to perform any unit tests on this code as both are coupled. Of course, we can do some amount of testing on the DAL but imagine if the DAL needs to be further extended to SQL and XML layers. If we need to that, implementation to extend it, becomes tedious and much more complicated. 

Hence based on the DIP we apply an Abstraction to decouple these layers.

 public class BusinessLogicLayer
{
    private readonly IRepositoryLayer DAL;

    public BusinessLogicLayer(IRepositoryLayer repositoryLayer)
    {
        DAL = repositoryLayer;
    }

    public void Save(Object details)
    {
        DAL.Save(details);
    }
}

public interface IRepositoryLayer
{
    void Save(Object details);
}

public class DataAccessLayer : IRepositoryLayer
{
    public void Save(Object details)
    {
        //perform save
    }
}

Adapter Design pattern can be seen as an example which is applying the dependency inversion principle.
Client
ITarget (interface) +Operation()
Adapter +Operation()
Adaptee +Specific Operation()
The high-level class defines its own adapter interface which is the abstraction that the other high-level
classes depend on. The Adaptee implementation also depends on the adapter interface abstraction.
*/

