
function pause.OnInit()

end

function pause.OnEnable()
	 Scene.OpenScene("scene1");
     Scene.SetOrder("pause", 1);
	 Scene.PauseScene("scene1");
end

function pause.Update(dt)
	
	if Input.SingleKeyPress(IKEY.SPACE) then
        Scene.HideScene("pause");
        Scene.PauseScene("pause");
		Scene.UnpauseScene("scene1");
	end

end

function pause.OnDisable()

end

function pause.OnDestroy()

end