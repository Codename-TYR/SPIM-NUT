//public class TestScript_01.js {

//}

function print1()
{
    return 2.3334333333333333333333333
}

function print2()
{
    console.log('print2 function')
}

function print3()
{
    console.log('print3 function')
}


function ActionMapping()
{
    /*    ScriptComponent.SetInputBinding()*/

    CppObject.scriptFunction(1);
/*    return __FUNCTION__ "Action Mapping Function from JS";*/
    return "Action Mapping Function from JS"
}

function ActionMapping_Jump()
{
/*    let*/



/*    return true;*/
}

function SetupInputBindings()
{
    // test 1 - call a slot in the class:
    Owner.signalOne.connect(ActionMapping);
    CppObject.signalTwo.connect(ActionMapping);
}