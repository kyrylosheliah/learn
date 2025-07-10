using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement; //для роботи зі сценами

public class SceneLoader : MonoBehaviour
{
    public void SceneLoad(int index) //завантажує сцену з вказаним індексом
    { 
        SceneManager.LoadScene(index);
    }

    public void QuitGame()
    {
        Application.Quit(); 
    }

    private void FixedUpdate()
    {
        if (Input.GetKey(KeyCode.Escape))  // якщо натиснуто Escape
    	{
        	SceneManager.LoadScene(0); //відкрити сцену Меню
    	}
    }
}
