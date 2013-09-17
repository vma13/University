# -*- coding: utf-8 -*-
class SchoolkidsController < ApplicationController
  #before_filter :check_admin_user, :except=>['index', 'show', 'search']

  def search
    @search = Schoolkid.search(params[:first_name], params[:second_name], 
                               params[:last_name])
  end
  
  def index
    @schoolkids = Schoolkid.page(params[:page])
  end

  def show
    @schoolkid = Schoolkid.includes(:school_group).find(params[:id])
  end

  def new
    @schoolkid = Schoolkid.new
  end

  def edit
    @schoolkid = Schoolkid.includes(:school_group).find(params[:id])
  end

  def create
    @schoolkid = Schoolkid.new(params[:schoolkid])
    if @schoolkid.save
      redirect_to @schoolkid, :notice => 'Школьник добавлен.'
    else
      render :action => "new"
    end
  end

  def update
    @schoolkid = Schoolkid.find(params[:id])
    if @schoolkid.update_attributes(params[:schoolkid])
      redirect_to @schoolkid, :notice => 'Школьник сохранен.'
    else
      render :action => "edit" 
    end
  end

  def destroy
    @schoolkid = Schoolkid.find(params[:id])
    @schoolkid.destroy
    redirect_to schoolkids_url, :notice=>"Школьник удален."
  end

 end
