#include "doctest.h"
#include <string>
#include <stdexcept>
#include <iostream>
#include <vector>
#include "OrgChart.hpp"
using namespace std;
using namespace ariel;

TEST_CASE(" organization1 ")
{
    OrgChart organization;
    organization.add_root("CEO")
        .add_sub("CEO", "CTO")    // Now the CTO is subordinate to the CEO
        .add_sub("CEO", "CFO")    // Now the CFO is subordinate to the CEO
        .add_sub("CEO", "COO")    // Now the COO is subordinate to the CEO
        .add_sub("CTO", "VP_SW")  // Now the VP Software is subordinate to the CTO
        .add_sub("COO", "VP_BI"); // Now the VP_BI is subordinate to the COO

    //   cout << organization << endl; /* Prints the org chart in a reasonable format. For example:
    //        CEO
    //        |--------|--------|
    //        CTO      CFO      COO
    //        |                 |
    //        VP_SW             VP_BI
    //  */


    CHECK_NOTHROW(organization.add_sub("VP_BI", "New Employee1"));
    CHECK_THROWS(organization.add_sub("ME", "New Employee"));
    CHECK_NOTHROW(organization.add_root("ME"));
    CHECK_NOTHROW(organization.add_sub("ME", "New Employee2"));
    CHECK_NOTHROW(organization.add_sub("New Employee2", "New Employee3"));
    CHECK_NOTHROW(organization.add_sub("VP_SW", "New Employee4"));
    CHECK_NOTHROW(organization.add_root("My Friend"));
    CHECK_NOTHROW(organization.add_sub("My Friend", "New Employee5"));
    

}


TEST_CASE(" organization2 "){
        OrgChart organization;
        CHECK_THROWS_MESSAGE(org.add_sub("Shani" , "David"), "can't add sub before root");
        CHECK_THROWS_MESSAGE(org.add_sub("David" , "Shani"), "can't add sub before root");
        CHECK_NOTHROW(org.add_root("Yonatan"));
        CHECK_NOTHROW(org.add_root("Samuel"));
        CHECK_NOTHROW(org.add_sub("Samuel" , "Shani"));
        CHECK_THROWS_MESSAGE(org.add_sub("Adi" , "Refhael"), "employer doesn't exist");
        CHECK_NOTHROW(org.add_sub("Samuel" , "Refhael"));
        CHECK_NOTHROW(org.add_sub("Refhael" , "Dan"));
        CHECK_NOTHROW(org.add_sub("Dan" , "Gabi"));
        CHECK_NOTHROW(org.add_sub("Shani", "Avigel"));
        CHECK_NOTHROW(org.add_sub("Shani", "Yossi"));
        CHECK_NOTHROW(org.add_sub("Samuel", "Shir"));
        CHECK_NOTHROW(org.add_sub("Gabi", "Shaked"));
        CHECK_NOTHROW(org.add_sub("Gabi", "Ofer"));


}


TEST_CASE(" check level_order, reverse_order,  preorder")
{
    vector<string> roles = {"CEO", "CTO", "CFO", "COO", "VP_SW", "New_Employee" , "VP_BI"};
    vector<string> level_order = {roles[0], roles[1], roles[2], roles[3], roles[4], roles[5], roles[6]};
    vector<string> reverse_order = {roles[4], roles[5], roles[6], roles[1], roles[2], roles[3], roles[0]};
    vector<string> preorder = {roles[0], roles[1], roles[4], roles[2], roles[5], roles[3], roles[6]};
    OrgChart organization;
    organization.add_root(roles[0])
        .add_sub(roles[0], roles[1])  // Now the CTO is subordinate to the CEO
        .add_sub(roles[0], roles[2])  // Now the CFO is subordinate to the CEO
        .add_sub(roles[0], roles[3])  // Now the COO is subordinate to the CEO
        .add_sub(roles[1], roles[4])  // Now the VP Software is subordinate to the CTO
        .add_sub(roles[3], roles[5]); // Now the VP_BI is subordinate to the CFO
        .add_sub(roles[2], roles[6]); // Now the New_Employee is subordinate to the COO
    //        CEO
    //        |--------|--------|
    //        CTO      CFO      COO
    //        |         |        |
    //        VP_SW     VP_BI    New_Employee
    //  */
    size_t i = 0;
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
    {
        CHECK_EQ(level_order[i++], (*it));
    } // Needs to be: CEO CTO CFO COO VP_SW VP_BI New_Employee

    i = 0;
    for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it)
    {
        CHECK_EQ(reverse_order[i++], (*it));
    } // Needs to be: VP_SW VP_BI New_Employee CTO CFO COO CEO

    i = 0;
    for (auto it = organization.begin_preorder(); it != organization.end_preorder(); ++it)
    {
        CHECK_EQ(preorder[i++], (*it));
    } // Needs to be: CEO CTO VP_SW CFO VP_BI COO New_Employee 

    i = 0;
    for (auto element : organization)
    { // this should work like level order
        CHECK_EQ(level_order[i++], element);
    } // Needs to be: CEO CTO CFO COO VP_SW VP_BI New_Employee

}

TEST_CASE(" create tree with one name ")
{
    OrgChart organization;
    CHECK_NOTHROW(organization.add_root("Shani"));
    for(size_t i=0; i<=10; i++)
    {
        CHECK_NOTHROW(organization.add_sub("Shani", "Shani"));
    }

}

TEST_CASE(" check tree without root ")
{
    OrgChart organization;
    CHECK_THROWS(organization.add_sub("child1", "child2"));
    CHECK_THROWS(organization.add_sub("child2", "child3"));
    CHECK_THROWS(organization.add_sub("child3", "child4"));
    CHECK_THROWS(organization.add_sub("child4", "child5"));
    CHECK_THROWS(organization.add_sub("child5", "child6"));
    CHECK_THROWS(organization.add_sub("child6", "child7"));
    CHECK_THROWS(organization.add_sub("child7", "child8"));
}
