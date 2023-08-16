using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


/**
The idea is that we have an Employee class that we wish to extend so that the bonus is calculated appropriately.
If we wish to calculate the bonus for a temporary emplyee (mabye consultant), we need to add EmployeeType to the
Employee class, then change CalculateBonus based on that...

Instead, we should use the code further down...
*/

namespace OpenClosedDemo
{
    public class Employee
    {
        Employee() { }
        public Employee(int id, string name, string type)
        {
            this.ID = id;
            this.Name = name;
            this.EmployeeType = type;
        }

        public int ID { get; set; }
        public string EmployeeType { get; set; }
        public string Name { get; set; }

        public decimal CalculateBonus(decimal salary)
        {
            if (this.EmployeeType == "Permanent")
                return salary * .1M;
            else
                return salary * .05M;
        }
    }
}

/**
Main class:

 namespace OpenClosedDemo
{
    class Program
    {
        static void Main(string[] args)
        {
            Employee empJohn = new Employee(1, "John", "Permanent" );
            Employee empJason = new Employee(2, "Jason", "Temp");
           
            Console.WriteLine(string.Format("Employee {0} Bonus: {1}",
                empJohn.ToString(),
                empJohn.CalculateBonus(100000).ToString()));
            Console.ReadLine();
        }
    }
}
*/

/**
Code after Open Closed Principle Implementation:

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OpenClosedDemo
{
    public abstract class Employee
    {
        public int ID { get; set; }
        public string Name { get; set; }
       
        public Employee()
        {
        }
        public Employee(int id, string name )
        {
            this.ID = id; this.Name = name; 
        }
        public abstract decimal CalculateBonus(decimal salary);
       
        public override string ToString()
        {
            return string.Format("ID : {0} Name : {1}", this.ID, this.Name);
        }
    }

    public class PermanentEmployee : Employee
    {
        public PermanentEmployee()
        { }

        public PermanentEmployee(int id, string name) : base(id, name)
        { }
        public override decimal CalculateBonus(decimal salary)
        {
            return salary * .1M;
        }
    }

    public class TemporaryEmployee : Employee
    {
        public TemporaryEmployee()
        { }

        public TemporaryEmployee(int id, string name) : base(id, name)
        { }
		
        public override decimal CalculateBonus(decimal salary)
        {
            return salary * .05M;
        }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OpenClosedDemo
{
    class Program
    {
        static void Main(string[] args)
        {
            Employee empJohn = new PermanentEmployee(1, "John"  );
            Employee empJason = new TemporaryEmployee(2, "Jason" );
           
            Console.WriteLine(string.Format("Employee {0} Bonus: {1}",
                empJohn.ToString(),
                empJohn.CalculateBonus(100000).ToString()));
				
            Console.WriteLine(string.Format("Employee {0} Bonus: {1}",
              empJason.ToString(),
              empJason.CalculateBonus(150000).ToString()));
            Console.ReadLine();
        }
    }
}

*/