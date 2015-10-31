
function game.OnInit()
	
end

function game.OnEnable()
   
end

function game.Update(dt)
  
    if Input.SingleKeyPress(IKEY.ESC) or Input.SingleKeyPress(IKEY.F2) then
        Game.Exit();
    end

    if Input.SingleKeyPress(IKEY.P) then
        Scene.ShowScene("pause");
        Scene.UnpauseScene("pause");
        Scene.PauseScene("scene1");
        --Scene.SetOrder("pause", 1);
    end

end

function game.OnDisable()
	
end

function game.OnDestroy()
	
end
