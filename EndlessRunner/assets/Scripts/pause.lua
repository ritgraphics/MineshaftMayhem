
function pause.OnInit()

end

function pause.OnEnable()
	 Scene.OpenScene("game");
     Scene.SetOrder("pause", 1);
	 Scene.PauseScene("game");
end

function pause.Update(dt)
	
	if Input.SingleKeyPress(IKEY.SPACE) then
        Scene.HideScene("pause");
        Scene.PauseScene("pause");
		Scene.UnpauseScene("game");
	end

end

function pause.OnDisable()

end

function pause.OnDestroy()

end