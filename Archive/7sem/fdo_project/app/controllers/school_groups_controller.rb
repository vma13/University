# -*- coding: utf-8 -*-
class SchoolGroupsController < ApplicationController
  before_filter :check_admin_user, :except=>['index', 'show'] 

  def index
    respond_to do |format|
      format.html{ @school_groups = SchoolGroup.page(params[:page]) }
      format.json do
        @school_groups = SchoolGroup.where("lower(number) LIKE lower(?)", "%#{params[:q]}%").all
        render :json => @school_groups.map(&:attributes)
      end
    end
  end

  def show
    @school_group = SchoolGroup.includes(:schoolkids).find(params[:id])
  end

  def new
    @school_group = SchoolGroup.new
  end

  def edit
    @school_group = SchoolGroup.find(params[:id])
  end

  def create
    @school_group = SchoolGroup.new(params[:school_group])
    if @school_group.save
      redirect_to @school_group, :notice => 'Класс добавлен.'
    else
      render :action => "new"
    end
  end

  def update
    @school_group = SchoolGroup.find(params[:id])
    if @school_group.update_attributes(params[:school_group])
      redirect_to @school_group, :notice => 'Класс сохранен.'
    else
      render :action => "edit"
    end
  end

  def destroy
    @school_group = SchoolGroup.find(params[:id])
    @school_group.destroy
    redirect_to groups_url, :notice => 'Кдасс удален.'
  end
end
