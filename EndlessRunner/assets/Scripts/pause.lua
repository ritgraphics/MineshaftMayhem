
function pause.OnInit()

end

function pause.OnEnable()

end

function pause.Update(dt)
	
	if Input.SingleKeyPress(IKEY.SPACE) then
		--need to unpause into the main scene
		print("Opening scene1");

        Scene.OpenScene("scene1");
        Scene.SetOrder("pause", 1);
        Scene.HideScene("pause");
        Scene.PauseScene("pause");
        
	end

end

function pause.OnDisable()

end

function pause.OnDestroy()

end