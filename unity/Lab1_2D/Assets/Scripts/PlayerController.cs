using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
public class PlayerController : MonoBehaviour
{
	public float speed; //швидкість
	public float jumpForce; //сила стрибку
	private float moveInput; //для отримання натискань клавіш руху
	private Rigidbody2D rb; //компонент Rigidbody2D
	private bool facingRight = true; //гравець дивиться праворуч


	private bool isGrounded; // чи приземлився персонаж
	public Transform feetPos; //позиція ніг
	public  float checkRadius; //радіус, як близько до землі має знаходитися персонаж
	public LayerMask whatIsGround; //шар, що є землею


	[SerializeField] private Animator anim;
	[SerializeField] private CanvasGroup inventoryScreen;


	private void Start()// стартова функція, працює при запуску гри
	{
		rb = GetComponent<Rigidbody2D>(); // отримуємо компонент Rigidbody2D
		anim = GetComponent<Animator>();
	}

	private void Update()//викликається кожен кадр
	{
		isGrounded = Physics2D.OverlapCircle(feetPos.position, checkRadius, whatIsGround);
		if (isGrounded == true && Input.GetKeyDown(KeyCode.Space)) //якщо приземлився та натиснуто Пробіл
		{
			rb.velocity = Vector2.up * jumpForce; //стрибок
			anim.SetTrigger("takeOf");
		}
		if(isGrounded == true)// якщо на землі
		{
			anim.SetBool("isJumping", false); // не відбувається стрибок
		}
		else 
		{
			anim.SetBool("isJumping", true); // відбувається стрибок
		}

		if (Input.GetKeyDown(KeyCode.F1))
		{
			foreach(Transform child in GameObject.Find("Background").transform)
    		{
        		child.GetComponent<Parallax>().parallaxEffect *= -1;
    		}
		}

		if (Input.GetKeyDown(KeyCode.Tab))
		{
			if (inventoryScreen.blocksRaycasts == true)
			{
				inventoryScreen.alpha = 0f;
				inventoryScreen.blocksRaycasts = false;
			}
			else
			{
				inventoryScreen.alpha = 1f;
				inventoryScreen.blocksRaycasts = true;
			}
			 //this makes everything transparent
			 //this prevents the UI element to receive input events
		}
	}


	private void FixedUpdate() // викликається фіксовану кількість разів на секунду, працюємо з фізикою та анімаціями 
	{
		moveInput = Input.GetAxis("Horizontal"); //використання горизонтальної осі, тобто рух лише ліворуч та праворуч
		rb.velocity = new Vector2(moveInput * speed, rb.velocity.y); //швидкість компоненту Rigidbody2D, змінюємо лише за х
		if (facingRight == false && moveInput > 0) //коли дивиться ліворуч і натиснуто праву клавішу 
		{
			Flip(true);// розгортаємо голову
			anim.SetTrigger("Idle");
		}
		else if (facingRight == true && moveInput < 0) //коли дивиться праворуч і натиснуто ліву клавішу 
		{
			Flip(false);// розгортаємо голову
			anim.SetTrigger("Idle");
		}

		if(moveInput == 0) //якщо не рухається
		{
			anim.SetBool("isRunning", false);
		}
		else
		{
			anim.SetBool("isRunning", true);
		}
	}
	void Flip(bool isFacingRight) //розгортання гравця
	{
		facingRight = isFacingRight;
		Vector3 Scaler = transform.localScale; //початкове положення
		Scaler.x *= -1; //змінюємо положення
		transform.localScale = Scaler; //застосувати зміни
	}
}
