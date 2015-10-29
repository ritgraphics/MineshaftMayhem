
function GameOver.OnInit()

end

function GameOver.OnEnable()
     Scene.SetOrder("GameOver", 2);
end

function GameOver.Update(dt)
	
	if Input.SingleKeyPress(IKEY.I) then
        Scene.HideScene("GameOver");
		Scene.UnpauseScene("scene1");
	end

end

function GameOver.OnDisable()

end

function GameOver.OnDestroy()

end