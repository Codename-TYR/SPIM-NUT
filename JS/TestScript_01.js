//public class TestScript_01.js {

//}

//function Tick()
//{
//    return 2.3334333333333333333333333
//}

function BeginPlay()
{
    console.log('print2 function')
}



function ActionMapping()
{
    /*    ScriptComponent.SetInputBinding()*/

/*    Owner.scriptFunction(1);*/
/*    return __FUNCTION__ "Action Mapping Function from JS";*/
    return "Action Mapping Function from JS"
}

const SpaceInput = '32'
const WInput = '87'
const AInput = '65'
const SInput = '83'
const DInput = '68'
const inputMap = {}

let JumpcooldownTracker = 2;
let Jumpcooldown = 2;

function Tick(inputs, deltaTime)
{
    const arrayOfInputs = inputs.split(' ')


    for (const input of arrayOfInputs) {
        const keysAndValues = input.split(',')
        inputMap[keysAndValues[0]] = keysAndValues[1] == '1' ? true : false
    }

    if (inputMap[SpaceInput] == true)
    {
        if (JumpcooldownTracker <= 0)
        {
            Owner.CallJump();
            JumpcooldownTracker = Jumpcooldown;
        }
    }
    if (inputMap[WInput] == true)
    {
        Owner.CallWInput();
    }
    if (inputMap[AInput] == true)
    {
        Owner.CallAInput();
    }
    if (inputMap[SInput] == true)
    {
        Owner.CallSInput();
    }
    if (inputMap[DInput] == true)
    {
        Owner.CallDInput();
    }

    JumpcooldownTracker -= deltaTime;


/*    "68,0 16777235,0 16777237,0 65,0 1,0 16777234,0 81,0 83,0 16777236,0 87,0 69,0 16777248,0 2,0 " */
/*
["68,0", "16777235,0", "65,0" ...]
*/


    /*    Owner.scriptFunction(1);*/

}


function takeMap(a)
{
    /*    console.log(a)*/

    return a
}


function ActionMapping2()
{
    /*    ScriptComponent.SetInputBinding()*/

/*    Owner.scriptFunction(1);*/
/*    return __FUNCTION__ "Action Mapping Function from JS";*/
    return "Action Mapping Function from JS"
}


//if (inputMap[SpaceInput] == true) {
//    /*        Owner.ActionMapping_Jump();*/
//    Owner.CallJump();
//}
//if (inputMap[WInput] == true) {
//    /*        Owner.ActionMapping_W();*/
//    Owner.CallWInput();
//}
//if (inputMap[AInput] == true) {
//    Owner.ActionMapping_A();
//}
//if (inputMap[SInput] == true) {
//    Owner.ActionMapping_S();
//}
//if (inputMap[DInput] == true) {
//    Owner.ActionMapping_D();
//}


function ActionMapping_Jump()
{
    /*    Owner.CallJump();*/

    if (inputMap[SpaceInput] == true)
    {
        /*        Owner.ActionMapping_Jump();*/
        Owner.CallJump();
    }

}
function ActionMapping_W()
{
    /*    Owner.CallWInput();*/

    if (inputMap[WInput] == true)
    {
        /*        Owner.ActionMapping_W();*/
        Owner.CallWInput();
    }
}
function ActionMapping_A()
{
    /*    Owner.CallAInput();*/

    if (inputMap[AInput] == true)
    {
        Owner.CallAInput();
    }

}
function ActionMapping_S()
{
    /*    Owner.CallSInput();*/
    if (inputMap[SInput] == true)
    {
        Owner.CallSInput();
    }

}
function ActionMapping_D()
{
    /*    Owner.CallDInput();*/

    if (inputMap[DInput] == true)
    {
        Owner.CallDInput();
    }

}

function SetupInputBindings()
{
    // test 1 - call a slot in the class:
    Owner.signal_1.connect(ActionMapping_Jump);
    Owner.signal_tick_1.connect(ActionMapping_W);
    Owner.signal_tick_2.connect(ActionMapping_A);
    Owner.signal_tick_3.connect(ActionMapping_S);
    Owner.signal_tick_4.connect(ActionMapping_D);
/*    CppObject.signalTwo.connect(ActionMapping);*/
}