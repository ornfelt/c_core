using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SRPDemo
{
	/**
	Code before SRP:
    interface IUser
    {
        bool Login(string username, string password);
        bool Register(string username, string password, string email);
        void LogError(string error);
        bool SendEmail(string emailContent);
    }
	*/
	
	interface IUser
    {
        bool Login(string username, string password);
        bool Register(string username, string password, string email);
    }
    interface ILogger
    {
        void LogError(string error);
    }

    interface IEmail
    {
        bool SendEmail(string emailContent);
    }
}